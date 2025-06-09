use std::io::{BufRead, stdin};

const TREE_LIM: usize = 2049;
const LEVEL_LIM: usize = 11;

fn ilog2(x: usize) -> usize {
    (usize::BITS - x.leading_zeros() - 1) as usize
}

#[derive(Clone, Copy, Debug, PartialEq)]
struct Node(u16, char);

#[derive(Clone)]
struct Tree {
    symbols: Vec<Option<Node>>,
}

impl Tree {
    fn new() -> Self {
        Self {
            symbols: vec![None; TREE_LIM],
        }
    }

    fn insert(&mut self, node: Node) {
        self.insert_recur(1, node);
    }

    fn insert_recur(&mut self, i0: usize, node: Node) {
        if let Some(node0) = self.symbols[i0] {
            let i1 = if node.0 <= node0.0 {
                i0 * 2
            } else {
                i0 * 2 + 1
            };
            self.insert_recur(i1, node);
        } else {
            self.symbols[i0] = Some(node);
        }
    }

    fn level_strings(&self) -> Vec<String> {
        self.symbols.iter().enumerate().fold(
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

fn parse_line(s: &str) -> [Node; 2] {
    let parts = s.split_whitespace().collect::<Vec<_>>();
    [parse_node(parts[2]), parse_node(parts[3])]
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let node_pairs: Vec<_> = lines.into_iter().map(|s| parse_line(&s)).collect();

    let mut trees = vec![Tree::new(); 2];
    for node_pair in node_pairs {
        for (i, node) in node_pair.into_iter().enumerate() {
            trees[i].insert(node);
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
