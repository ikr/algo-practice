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

    fn adopt(&mut self, nss: &[NodeSource], i_root: usize, i_orphan: usize) -> bool {
        let root_node = self.nodes[i_root];

        match (root_node.left, root_node.right) {
            (None, _) if Self::weak_bond(&nss[i_root].left_socket, &nss[i_orphan].plug) => {
                self.plug_into(SocketPointer::new(i_root, Branch::L), i_orphan);
                true
            }
            (Some(i_left), _)
                if Self::strictly_weak_bond(&nss[i_root].left_socket, &nss[i_left].plug)
                    && Self::strong_bond(&nss[i_root].left_socket, &nss[i_orphan].plug) =>
            {
                self.plug_into(SocketPointer::new(i_root, Branch::L), i_orphan);
                self.adopt(nss, i_root, i_left)
            }
            (Some(i_left), _) if self.adopt(nss, i_left, i_orphan) => true,
            (_, None) if Self::weak_bond(&nss[i_root].right_socket, &nss[i_orphan].plug) => {
                self.plug_into(SocketPointer::new(i_root, Branch::R), i_orphan);
                true
            }
            (_, Some(i_right))
                if Self::strictly_weak_bond(&nss[i_root].right_socket, &nss[i_right].plug)
                    && Self::strong_bond(&nss[i_root].right_socket, &nss[i_orphan].plug) =>
            {
                self.plug_into(SocketPointer::new(i_root, Branch::R), i_orphan);
                self.adopt(nss, i_root, i_right)
            }
            (_, Some(i_right)) if self.adopt(nss, i_right, i_orphan) => true,
            _ => false,
        }
    }

    fn new(n: usize) -> Self {
        Self {
            nodes: vec![Node::new(); n],
        }
    }

    fn build_from_source(&mut self, nss: Vec<NodeSource>) {
        for i in 1..nss.len() {
            assert!(self.adopt(&nss, 0, i));
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
