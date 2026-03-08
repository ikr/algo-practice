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

#[derive(Debug)]
struct NodeIndex {
    shapes: Vec<String>,
}

impl NodeIndex {
    fn new(nss: &[NodeSource]) -> Self {
        let shapes = nss.iter().map(|ns| ns.plug.clone()).collect();
        Self { shapes }
    }

    fn index_of(&self, key: &str) -> usize {
        self.shapes.iter().position(|x| x == key).unwrap()
    }
}

#[derive(Clone, Copy, Debug)]
enum Branch {
    L,
    R,
}

#[derive(Debug)]
struct Graph {
    nodes: Vec<Node>,
}

impl Graph {
    fn new(nss: Vec<NodeSource>) -> Self {
        fn connection_socket(
            nss: &[NodeSource],
            nodes: &[Node],
            root: &NodeSource,
            orphan: &NodeSource,
        ) -> Option<(usize, Branch)> {
            eprintln!("{:?}", root);
            let nidx = NodeIndex::new(nss);
            let root_index = nidx.index_of(&root.plug);
            let root_node = nodes[root_index];

            if root_node.left.is_none() && root.left_socket == orphan.plug {
                Some((root_index, Branch::L))
            } else if let Some(li) = root_node.left
                && let Some(left_subtree_result) = connection_socket(nss, nodes, &nss[li], orphan)
            {
                Some(left_subtree_result)
            } else if root_node.right.is_none() && root.right_socket == orphan.plug {
                Some((root_index, Branch::R))
            } else if let Some(ri) = root_node.right
                && let Some(right_subtree_result) = connection_socket(nss, nodes, &nss[ri], orphan)
            {
                Some(right_subtree_result)
            } else {
                None
            }
        }

        let mut nodes = vec![Node::new(); nss.len()];

        for (i, ns) in nss.iter().enumerate().skip(1) {
            let (u, branch) = connection_socket(&nss, &nodes, &nss[0], ns).unwrap();

            match branch {
                Branch::L => {
                    assert!(nodes[u].left.is_none());
                    nodes[u].left = Some(i);
                }
                Branch::R => {
                    assert!(nodes[u].right.is_none());
                    nodes[u].right = Some(i);
                }
            }
        }

        Self { nodes }
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let nss: Vec<NodeSource> = lines.into_iter().map(NodeSource::parse).collect();
    let g = Graph::new(nss);
    eprintln!("{:?}", g);
}
