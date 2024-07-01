use regex::Regex;
use std::{
    collections::HashSet,
    io::{self, BufRead},
};

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i8, i8);

#[derive(Clone, Copy, Debug)]
struct Node {
    crd: Crd,
    cap: i32,
    usd: i32,
}

impl Node {
    fn parse_file_path(src: &str) -> Crd {
        let re = Regex::new(r"^/dev/grid/node-x(\d+)-y(\d+)$").unwrap();
        let caps = re.captures(src).unwrap();
        let [x, y] = caps
            .iter()
            .skip(1)
            .map(|s| s.unwrap().as_str().parse::<i8>().unwrap())
            .collect::<Vec<_>>()[..]
        else {
            panic!("Not enough captured")
        };
        Crd(x, y)
    }

    fn parse_tbs(src: &str) -> i32 {
        src.strip_suffix('T').unwrap().parse::<i32>().unwrap()
    }

    fn parse(src: &str) -> Node {
        let parts: Vec<&str> = src.split_whitespace().collect();
        Node {
            crd: Node::parse_file_path(parts[0]),
            cap: Node::parse_tbs(parts[1]),
            usd: Node::parse_tbs(parts[2]),
        }
    }
}

fn non_empty_a_fits_in_b(a: Node, b: Node) -> bool {
    if a.usd > 0 {
        b.cap - b.usd >= a.usd
    } else {
        false
    }
}

#[derive(Clone, Copy, Debug)]
struct Vertex {
    empty_cell: Crd,
    payload_cell: Crd,
}

struct Cluster {
    width: i8,
    height: i8,
    blocked_cells: HashSet<Crd>,
    empty_cell: Crd,
    source_cell: Crd,
    destination_cell: Crd,
}

impl Cluster {
    fn new(width: i8, height: i8, blocked_cells: HashSet<Crd>, empty_cell: Crd) -> Cluster {
        Cluster {
            width,
            height,
            blocked_cells,
            empty_cell,
            source_cell: Crd(width - 1, 0),
            destination_cell: Crd(0, 0),
        }
    }

    fn in_bounds(&self, crd: Crd) -> bool {
        let Crd(x, y) = crd;
        0 <= x && x < self.width && 0 <= y && y < self.height
    }

    fn adjacent(&self, u: Vertex) -> Vec<Vertex> {
        let Crd(x0, y0) = u.empty_cell;
        let mut result: Vec<Vertex> = vec![];

        for (x, y) in [(x0, y0 - 1), (x0 + 1, y0), (x0, y0 + 1), (x0 - 1, y0)] {
            if self.in_bounds(Crd(x, y)) && !self.blocked_cells.contains(&Crd(x, y)) {
                if Crd(x, y) == u.payload_cell {
                    result.push(Vertex {
                        empty_cell: Crd(x, y),
                        payload_cell: Crd(x0, y0),
                    });
                } else {
                    result.push(Vertex {
                        empty_cell: Crd(x, y),
                        payload_cell: u.payload_cell,
                    });
                }
            }
        }
        result
    }
}

fn main() {
    let nodes: Vec<Node> = io::stdin()
        .lock()
        .lines()
        .skip(2)
        .map(|line| Node::parse(&line.unwrap()))
        .collect();

    let mut result = 0;
    for (i, a) in nodes.iter().enumerate() {
        for b in &nodes[i + 1..] {
            if non_empty_a_fits_in_b(*a, *b) || non_empty_a_fits_in_b(*b, *a) {
                result += 1;
            }
        }
    }
    println!("{}", result);

    let min_cap = nodes.iter().map(|n| n.cap).min().unwrap();
    eprintln!("min_cap: {}", min_cap);

    let width = nodes.iter().map(|n| n.crd.0).max().unwrap() + 1;
    let height = nodes.iter().map(|n| n.crd.1).max().unwrap() + 1;
    eprintln!("{}x{} grid", width, height);

    let blocked_cells: HashSet<Crd> = nodes
        .iter()
        .filter(|n| n.usd > min_cap)
        .map(|n| n.crd)
        .collect();
    eprintln!("blocked: {:?}", blocked_cells);

    let empty_cell: Crd = nodes.iter().find(|n| n.usd == 0).unwrap().crd;
    eprintln!("empty: {:?}", empty_cell);

    let cluster = Cluster::new(width, height, blocked_cells, empty_cell);
}
