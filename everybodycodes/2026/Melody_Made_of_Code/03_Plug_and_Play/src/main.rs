use itertools::Itertools;
use regex::Regex;
use std::fmt::{Display, Formatter, Result};
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

#[derive(Clone, Copy, Debug)]
struct Node {
    left: Option<usize>,
    right: Option<usize>,
}

impl Node {
    fn new() -> Self {
        Self {
            left: None,
            right: None,
        }
    }
}

impl Display for Node {
    fn fmt(&self, f: &mut Formatter<'_>) -> Result {
        match (self.left, self.right) {
            (None, None) => write!(f, "(- -)"),
            (None, Some(r)) => write!(f, "(- {})", r + 1),
            (Some(l), None) => write!(f, "({} -)", l + 1),
            (Some(l), Some(r)) => write!(f, "({} {})", l + 1, r + 1),
        }
    }
}

#[derive(Clone, Copy, Debug)]
enum Branch {
    L,
    R,
}

#[derive(Clone, Copy, Debug)]
struct SocketPointer {
    node_index: usize,
    branch: Branch,
}

impl SocketPointer {
    fn new(node_index: usize, branch: Branch) -> Self {
        Self { node_index, branch }
    }
}

#[derive(Debug)]
struct Graph {
    nodes: Vec<Node>,
    orphan: Option<usize>,
}

impl Graph {
    fn strong_bond(shape_a: &str, shape_b: &str) -> bool {
        shape_a == shape_b
    }

    fn weak_bond(shape_a: &str, shape_b: &str) -> bool {
        let (a, b) = shape_a.split(' ').collect_tuple().unwrap();
        let (p, q) = shape_b.split(' ').collect_tuple().unwrap();
        a == p || b == q
    }

    fn strictly_weak_bond(shape_a: &str, shape_b: &str) -> bool {
        Self::weak_bond(shape_a, shape_b) && !Self::strong_bond(shape_a, shape_b)
    }

    fn plug_into(&mut self, ptr: SocketPointer, node_index: usize) {
        match ptr.branch {
            Branch::L => {
                self.nodes[ptr.node_index].left = Some(node_index);
            }
            Branch::R => {
                self.nodes[ptr.node_index].right = Some(node_index);
            }
        }
    }

    fn adopt(&mut self, nss: &[NodeSource], i_root: usize) {
        let root_node = self.nodes[i_root];
        if let Some(i_orphan) = self.orphan {
            match root_node.left {
                None if Self::weak_bond(&nss[i_root].left_socket, &nss[i_orphan].plug) => {
                    self.plug_into(SocketPointer::new(i_root, Branch::L), i_orphan);
                    self.orphan = None;
                }
                Some(i_left)
                    if Self::strictly_weak_bond(&nss[i_root].left_socket, &nss[i_left].plug)
                        && Self::strong_bond(&nss[i_root].left_socket, &nss[i_orphan].plug) =>
                {
                    self.plug_into(SocketPointer::new(i_root, Branch::L), i_orphan);
                    self.orphan = Some(i_left);
                }
                Some(i_left) => self.adopt(nss, i_left),
                _ => {}
            }
        }

        if let Some(i_orphan) = self.orphan {
            match root_node.right {
                None if Self::weak_bond(&nss[i_root].right_socket, &nss[i_orphan].plug) => {
                    self.plug_into(SocketPointer::new(i_root, Branch::R), i_orphan);
                    self.orphan = None;
                }
                Some(i_right)
                    if Self::strictly_weak_bond(&nss[i_root].right_socket, &nss[i_right].plug)
                        && Self::strong_bond(&nss[i_root].right_socket, &nss[i_orphan].plug) =>
                {
                    self.plug_into(SocketPointer::new(i_root, Branch::R), i_orphan);
                    self.orphan = Some(i_right);
                }
                Some(i_right) => self.adopt(nss, i_right),
                _ => {}
            }
        }
    }

    fn new(n: usize) -> Self {
        Self {
            nodes: vec![Node::new(); n],
            orphan: None,
        }
    }

    fn build_from_source(&mut self, nss: Vec<NodeSource>) {
        for i in 1..nss.len() {
            self.orphan = Some(i);

            while self.orphan.is_some() {
                self.adopt(&nss, 0);
            }
        }
    }

    fn in_order_traversal(&self, i_root: usize) -> Vec<usize> {
        let mut result = if let Some(i_left) = self.nodes[i_root].left {
            self.in_order_traversal(i_left)
        } else {
            vec![]
        };

        result.push(i_root);

        let suff = if let Some(i_right) = self.nodes[i_root].right {
            self.in_order_traversal(i_right)
        } else {
            vec![]
        };

        result.extend(suff);
        result
    }
}

// fn represent_nodes(nodes: &[Node]) -> String {
//     nodes
//         .iter()
//         .map(|node| format!("{}", node).to_string())
//         .join(" ")
// }

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let nss: Vec<NodeSource> = lines.into_iter().map(NodeSource::parse).collect();
    let mut g = Graph::new(nss.len());
    g.build_from_source(nss);

    let traversed_ids = g
        .in_order_traversal(0)
        .into_iter()
        .map(|i| i + 1)
        .collect::<Vec<_>>();

    let result: usize = traversed_ids
        .into_iter()
        .enumerate()
        .map(|(i, id)| id * (i + 1))
        .sum();

    println!("{result}");
}
