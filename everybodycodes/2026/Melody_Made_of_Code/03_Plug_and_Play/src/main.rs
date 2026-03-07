use itertools::Itertools;
use regex::Regex;
use std::io::{BufRead, stdin};

#[derive(Debug)]
struct NodeSource {
    plug: String,
    left_socket: String,
    right_socket: String,
}

impl NodeSource {
    fn parse(s: String) -> Self {
        let r = r"^id=(\d+), plug=([A-Z]+ [A-Z]+), leftSocket=([A-Z]+ [A-Z]+), rightSocket=([A-Z]+ [A-Z]+), data=.+$";
        let re = Regex::new(r).unwrap();

        let (_, _, plug, left_socket, right_socket) = re
            .captures(&s)
            .unwrap()
            .iter()
            .map(|a| a.unwrap().as_str().to_string())
            .collect_tuple()
            .unwrap();

        Self {
            plug,
            left_socket,
            right_socket,
        }
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let nss: Vec<NodeSource> = lines.into_iter().map(NodeSource::parse).collect();
    eprintln!("{:?}", nss);
}
