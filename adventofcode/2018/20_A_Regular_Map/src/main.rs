use std::{
    collections::{HashMap, HashSet},
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
    program: Vec<char>,
}

impl Area {
    fn new(program: Vec<char>) -> Self {
        Area {
            graph: Graph::new(),
            program,
        }
    }

    fn explore_term(&mut self, u: Vert, ip: usize) -> (Vert, usize) {
        let mut i = ip;
        let mut v = u;
        loop {
            assert!(i < self.program.len());
            assert!(Dir::is_valid(self.program[i]));
            let dir = Dir::decode(self.program[i]);
            let w = v.move_to(dir);
            self.graph.connect(v, w);

            v = w;
            i += 1;
            if !Dir::is_valid(self.program[i]) {
                return (v, i);
            }
        }
    }

    fn explore(&mut self, u: Vert, ip: usize) -> (HashSet<Vert>, usize) {
        let mut result = HashSet::new();
        let mut i = ip;

        loop {
            if i == self.program.len() {
                return (result, ip);
            }

            match self.program[i] {
                '(' | '^' => {
                    let (vs, j) = self.explore(u, i + 1);
                    result.extend(vs);
                    i = j;
                }
                ')' | '$' => return (result, i + 1),
                '|' => {
                    i += 1;
                    continue;
                }
                _ => {
                    let (v, j) = self.explore_term(u, i);
                    result.insert(v);
                    i = j;
                }
            }
        }
    }
}

fn read_program() -> Vec<char> {
    let mut line = String::new();
    io::stdin().read_line(&mut line).unwrap();
    line.trim().chars().collect()
}

fn main() {
    let mut area = Area::new(read_program());
    area.explore(Vert(0, 0), 0);
    eprintln!("{:?}", area.graph.adj);
}
