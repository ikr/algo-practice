use std::io::{BufRead, stdin};

const TREE_LIM: usize = 1 << 24;
const LEVEL_LIM: usize = 25;

enum Cmd {
    Add(Node, Node),
    Swap(usize),
}

impl Cmd {
    fn parse(s: &str) -> Self {
        if s.starts_with("ADD") {
            let parts = s.split_whitespace().collect::<Vec<_>>();
            Self::Add(parse_node(parts[2]), parse_node(parts[3]))
        } else {
            let i = s.strip_prefix("SWAP ").unwrap().parse().unwrap();
            Self::Swap(i)
        }
    }
}

fn ilog2(x: usize) -> usize {
    (usize::BITS - x.leading_zeros() - 1) as usize
}

#[derive(Clone, Copy, Debug, PartialEq)]
struct Node(u16, char);

#[derive(Clone)]
struct Tree {
    nodes: Vec<Option<Node>>,
}

impl Tree {
    fn new() -> Self {
        Self {
            nodes: vec![None; TREE_LIM],
        }
    }

    fn insert(&mut self, node: Node) -> usize {
        self.insert_recur(1, node)
    }

    fn insert_recur(&mut self, i0: usize, node: Node) -> usize {
        if let Some(node0) = self.nodes[i0] {
            let i1 = if node.0 <= node0.0 {
                i0 * 2
            } else {
                i0 * 2 + 1
            };
            self.insert_recur(i1, node)
        } else {
            self.nodes[i0] = Some(node);
            i0
        }
    }

    fn level_strings(&self) -> Vec<String> {
        self.nodes.iter().enumerate().fold(
            vec![String::new(); LEVEL_LIM],
            |mut acc, (i, maybe_node)| {
                if let Some(node) = maybe_node {
                    let l = ilog2(i);
                    acc[l].push(node.1);
                }
                acc
            },
        )
    }

    fn longest_level_string(&self) -> String {
        self.level_strings()
            .into_iter()
            .max_by_key(|s| s.len())
            .unwrap()
    }
}

fn parse_node(s: &str) -> Node {
    let kv = s.split('=').collect::<Vec<_>>();
    let vv = kv[1]
        .strip_prefix('[')
        .and_then(|a| a.strip_suffix(']'))
        .unwrap();
    let rank_symbol = vv.split(',').collect::<Vec<_>>();
    Node(
        rank_symbol[0].parse().unwrap(),
        rank_symbol[1].chars().next().unwrap(),
    )
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let commands: Vec<_> = lines.into_iter().map(|s| Cmd::parse(&s)).collect();

    let mut tangled_indices: Vec<(usize, usize)> = vec![(0, 0)];
    let mut trees = vec![Tree::new(); 2];

    for cmd in commands {
        match cmd {
            Cmd::Add(left_tree_node, right_tree_node) => {
                let i = trees[0].insert(left_tree_node);
                let j = trees[1].insert(right_tree_node);
                tangled_indices.push((i, j));
            }
            Cmd::Swap(i) => {
                let (left_tree_index, right_tree_index) = tangled_indices[i];
                (
                    trees[0].nodes[left_tree_index],
                    trees[1].nodes[right_tree_index],
                ) = (
                    trees[1].nodes[right_tree_index],
                    trees[0].nodes[left_tree_index],
                );
            }
        }
    }

    let result = trees
        .into_iter()
        .map(|t| t.longest_level_string())
        .collect::<Vec<_>>()
        .join("");
    println!("{}", result);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_parse_noed() {
        assert_eq!(parse_node("left=[146,E]"), Node(146, 'E'));
        assert_eq!(parse_node("right=[283,!]"), Node(283, '!'));
    }
}
