use std::{
    collections::{HashMap, HashSet, VecDeque},
    io,
};

#[derive(Copy, Clone)]
enum Dir {
    N,
    E,
    S,
    W,
}

impl Dir {
    fn decode(c: char) -> Self {
        match c {
            'N' => Dir::N,
            'E' => Dir::E,
            'S' => Dir::S,
            'W' => Dir::W,
            _ => panic!("Invalid Dir {}", c),
        }
    }

    fn is_valid(c: char) -> bool {
        matches!(c, 'N' | 'E' | 'S' | 'W')
    }
}

#[derive(Copy, Clone)]
struct AstTerm(Dir);

struct AstSeq(Vec<AstNode>);
struct AstAlt(Vec<AstNode>);

enum AstNode {
    Seq(AstSeq),
    Alt(AstAlt),
    Term(AstTerm),
}

impl AstSeq {
    fn parse(program: &[char]) -> (Self, &[char]) {
        let mut result: Vec<AstNode> = Vec::new();
        let mut rest = program;
        loop {
            assert!(!rest.is_empty());
            match rest[0] {
                '$' => {
                    rest = &rest[1..];
                    break;
                }
                // Leave it to Alt's parsing
                ')' | '|' => break,
                '(' => {
                    let (sub, rest_) = AstAlt::parse(&rest[1..]);
                    result.push(AstNode::Alt(sub));
                    rest = rest_;
                }
                _ => {
                    assert!(Dir::is_valid(rest[0]));
                    let (sub, rest_) = AstTerm::parse(rest);
                    result.push(AstNode::Term(sub));
                    rest = rest_;
                }
            }
        }
        (Self(result), rest)
    }

    fn srt(&self) -> String {
        let mut result: String = "(".to_string();
        for node in &self.0 {
            result.push(' ');
            result.push_str(&node.str());
        }
        result.push(')');
        result
    }
}

impl AstAlt {
    fn parse(program: &[char]) -> (Self, &[char]) {
        let mut result: Vec<AstNode> = Vec::new();
        let mut rest = program;
        loop {
            assert!(!rest.is_empty());
            match rest[0] {
                ')' => {
                    rest = &rest[1..];
                    break;
                }
                '|' => {
                    let (sub, rest_) = AstSeq::parse(&rest[1..]);
                    result.push(AstNode::Seq(sub));
                    rest = rest_;
                }
                '(' => panic!("Unexpected `(` inside of an Alt"),
                '$' => panic!("Unexpected `$` inside of an Alt"),
                _ => {
                    let (sub, rest_) = AstSeq::parse(rest);
                    result.push(AstNode::Seq(sub));
                    rest = rest_;
                }
            }
        }
        (Self(result), rest)
    }

    fn srt(&self) -> String {
        let mut result: String = "(|".to_string();
        for node in &self.0 {
            result.push(' ');
            result.push_str(&node.str());
        }
        result.push(')');
        result
    }
}

impl AstTerm {
    fn parse(program: &[char]) -> (Self, &[char]) {
        assert!(!program.is_empty());
        (Self(Dir::decode(program[0])), &program[1..])
    }

    fn srt(&self) -> String {
        match self.0 {
            Dir::N => "N",
            Dir::E => "E",
            Dir::S => "S",
            Dir::W => "W",
        }
        .to_string()
    }
}

impl AstNode {
    fn parse(program: &[char]) -> Self {
        assert!(!program.is_empty());
        assert!(program[0] == '^');
        AstNode::Seq(AstSeq::parse(&program[1..]).0)
    }

    fn str(&self) -> String {
        match self {
            AstNode::Seq(seq) => seq.srt(),
            AstNode::Alt(alt) => alt.srt(),
            AstNode::Term(term) => term.srt(),
        }
    }
}

#[derive(Copy, Clone, Eq, Hash, PartialEq, Debug)]
struct Vert(i32, i32);

impl Vert {
    fn move_to(&self, dir: Dir) -> Self {
        match dir {
            Dir::N => Vert(self.0, self.1 + 1),
            Dir::E => Vert(self.0 + 1, self.1),
            Dir::S => Vert(self.0, self.1 - 1),
            Dir::W => Vert(self.0 - 1, self.1),
        }
    }
}

struct Graph {
    adj: HashMap<Vert, HashSet<Vert>>,
}

impl Graph {
    fn new() -> Self {
        Graph {
            adj: HashMap::new(),
        }
    }

    fn connect(&mut self, u: Vert, v: Vert) {
        self.adj.entry(u).or_default().insert(v);
        self.adj.entry(v).or_default().insert(u);
    }

    fn distances_from(&self, u0: Vert) -> HashMap<Vert, i32> {
        let mut result: HashMap<Vert, i32> = HashMap::new();
        let mut queue: VecDeque<Vert> = VecDeque::new();
        queue.push_back(u0);
        result.insert(u0, 0);
        while let Some(u) = queue.pop_front() {
            let d = result[&u];
            for &v in self.adj[&u].iter() {
                if !result.contains_key(&v) {
                    result.insert(v, d + 1);
                    queue.push_back(v);
                }
            }
        }
        result
    }
}

struct Area {
    graph: Graph,
}

impl Area {
    fn new() -> Self {
        Area {
            graph: Graph::new(),
        }
    }

    fn explore(&mut self, us: &[Vert], n: &AstNode) -> Vec<Vert> {
        let mut result: Vec<Vert> = Vec::new();
        for u in us {
            match n {
                AstNode::Seq(ref xs) => {
                    let mut cur: Vec<Vert> = vec![*u];
                    for x in &xs.0 {
                        cur = self.explore(&cur, x);
                    }
                    result.extend(cur);
                }
                AstNode::Alt(xs) => {
                    for x in &xs.0 {
                        result.extend(self.explore(&[*u], x));
                    }
                    eprintln!(
                        "vertices: {}  gen-size: {}",
                        self.graph.adj.len(),
                        result.len()
                    );
                }
                AstNode::Term(x) => {
                    let v = u.move_to(x.0);
                    self.graph.connect(*u, v);
                    result.push(v);
                }
            }
        }
        result
    }
}

fn read_program() -> Vec<char> {
    let mut line = String::new();
    io::stdin().read_line(&mut line).unwrap();
    line.trim().chars().collect()
}

fn main() {
    let program = read_program();
    let ast = AstNode::parse(&program);
    eprintln!("{}", &ast.str());

    let mut area = Area::new();
    area.explore(&[Vert(0, 0)], &ast);
    eprintln!("{:?}", area.graph.adj);

    let ds = area.graph.distances_from(Vert(0, 0));
    let result = ds.values().max().unwrap();
    println!("{}", result);
}
