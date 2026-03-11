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

    fn connection_socket(
        nss: &[NodeSource],
        nodes: &[Node],
        i_root: usize,
        i_orphan: usize,
    ) -> Option<SocketPointer> {
        let root_node = nodes[i_root];

        if root_node.left.is_none()
            && Self::weak_bond(&nss[i_root].left_socket, &nss[i_orphan].plug)
        {
            Some(SocketPointer::new(i_root, Branch::L))
        } else if let Some(i_left) = root_node.left
            && let Some(left_subtree_result) = Self::connection_socket(nss, nodes, i_left, i_orphan)
        {
            Some(left_subtree_result)
        } else if root_node.right.is_none()
            && Self::weak_bond(&nss[i_root].right_socket, &nss[i_orphan].plug)
        {
            Some(SocketPointer::new(i_root, Branch::R))
        } else if let Some(i_right) = root_node.right
            && let Some(right_subtree_result) =
                Self::connection_socket(nss, nodes, i_right, i_orphan)
        {
            Some(right_subtree_result)
        } else {
            None
        }
    }

    fn new(nss: Vec<NodeSource>) -> Self {
        let n = nss.len();
        let mut nodes = vec![Node::new(); n];

        for i in 1..n {
            let ptr = Self::connection_socket(&nss, &nodes, 0, i).unwrap();

            match ptr.branch {
                Branch::L => {
                    assert!(nodes[ptr.node_index].left.is_none());
                    nodes[ptr.node_index].left = Some(i);
                }
                Branch::R => {
                    assert!(nodes[ptr.node_index].right.is_none());
                    nodes[ptr.node_index].right = Some(i);
                }
            }
        }

        Self { nodes }
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
    let g = Graph::new(nss);

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
