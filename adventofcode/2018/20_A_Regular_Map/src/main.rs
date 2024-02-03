use std::{
    collections::{HashMap, HashSet},
    io,
};

#[derive(Copy, Clone, Debug)]
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

    fn explore(&mut self, u: Vert, n: AstNode) {
        todo!();
    }
}

#[derive(Clone, Debug)]
enum AstNode {
    Seq(Vec<AstNode>),
    Alt(Vec<AstNode>),
    Term(Dir),
}

impl AstNode {
    fn root() -> Self {
        AstNode::Seq(Vec::new())
    }
}

fn read_program_drop_caret_and_dollar() -> Vec<char> {
    let mut line = String::new();
    io::stdin().read_line(&mut line).unwrap();
    let mut result: Vec<char> = line.trim().chars().skip(1).collect();
    result.pop();
    result
}

fn main() {
    let program = read_program_drop_caret_and_dollar();
    let mut area = Area::new();
    area.explore(Vert(0, 0), AstNode::root());
    eprintln!("{:?}", area.graph.adj);
}
