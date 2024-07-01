use regex::Regex;
use std::io::{self, BufRead};

#[derive(Clone, Copy, Debug)]
struct Crd(i32, i32);

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
            .map(|s| s.unwrap().as_str().parse::<i32>().unwrap())
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
}
