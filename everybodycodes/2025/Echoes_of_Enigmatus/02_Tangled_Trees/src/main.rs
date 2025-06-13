use std::{
    collections::{BTreeMap, VecDeque},
    io::{BufRead, stdin},
};

const LEVEL_LIM: usize = 64;

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
    nodes: BTreeMap<usize, Node>,
}

impl Tree {
    fn new() -> Self {
        Self {
            nodes: BTreeMap::new(),
        }
    }

    fn insert(&mut self, node: Node) {
        self.insert_recur(1, node)
    }

    fn insert_recur(&mut self, i0: usize, node: Node) {
        if let Some(node0) = self.nodes.get(&i0) {
            let i1 = if node.0 < node0.0 { i0 * 2 } else { i0 * 2 + 1 };
            self.insert_recur(i1, node);
        } else {
            self.nodes.insert(i0, node);
        }
    }

    fn level_strings(&self) -> Vec<String> {
        self.nodes
            .iter()
            .fold(vec![String::new(); LEVEL_LIM], |mut acc, (i, node)| {
                let l = ilog2(*i);
                acc[l].push(node.1);
                acc
            })
    }

    fn longest_level_string(&self) -> String {
        self.level_strings()
            .into_iter()
            .enumerate()
            .max_by_key(|(level, s)| (s.len(), -(*level as i8)))
            .unwrap()
            .1
    }

    fn find_rank(&self, r: u16) -> Option<usize> {
        self.nodes
            .iter()
            .find(|(_, node)| node.0 == r)
            .map(|(i, _)| *i)
    }

    fn eject_subtree(&mut self, i0: usize) -> Vec<Node> {
        assert!(self.nodes.contains_key(&i0));
        let mut result: Vec<Node> = vec![];
        let mut q: VecDeque<usize> = VecDeque::from([i0]);

        while let Some(i) = q.pop_front() {
            result.push(*self.nodes.get(&i).unwrap());
            self.nodes.remove(&i);

            for j in [i * 2, i * 2 + 1] {
                if self.nodes.contains_key(&j) {
                    q.push_back(j);
                }
            }
        }

        result
    }

    fn copy_subtree(&self, i0: usize) -> Vec<Node> {
        assert!(self.nodes.contains_key(&i0));
        let mut result: Vec<Node> = vec![];
        let mut q: VecDeque<usize> = VecDeque::from([i0]);

        while let Some(i) = q.pop_front() {
            result.push(*self.nodes.get(&i).unwrap());

            for j in [i * 2, i * 2 + 1] {
                if self.nodes.contains_key(&j) {
                    q.push_back(j);
                }
            }
        }

        result
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

    let mut tangled_ranks: Vec<(u16, u16)> = vec![(0, 0)];
    let mut trees = vec![Tree::new(); 2];

    for cmd in commands {
        match cmd {
            Cmd::Add(left_tree_node, right_tree_node) => {
                trees[0].insert(left_tree_node);
                trees[1].insert(right_tree_node);
                tangled_ranks.push((left_tree_node.0, right_tree_node.0));
            }
            Cmd::Swap(id) => {
                let (rank_a, rank_b) = tangled_ranks[id];

                let (ii, i, jj, j) = [
                    (0usize, rank_a, 1usize, rank_b),
                    (0, rank_b, 1, rank_a),
                    (0, rank_a, 0, rank_b),
                    (1, rank_a, 1, rank_b),
                ]
                .into_iter()
                .filter_map(|(p, a, q, b)| {
                    if let (Some(i), Some(j)) = (trees[p].find_rank(a), trees[q].find_rank(b)) {
                        Some((p, i, q, j))
                    } else {
                        None
                    }
                })
                .next()
                .unwrap();

                let copy_a = trees[ii].copy_subtree(i);
                let copy_b = trees[jj].copy_subtree(j);
                if copy_a
                    .iter()
                    .any(|node| node.0 == trees[jj].nodes.get(&j).unwrap().0)
                    || copy_b
                        .iter()
                        .any(|node| node.0 == trees[ii].nodes.get(&i).unwrap().0)
                {
                    assert_eq!(ii, jj);
                    eprintln!("Must swap subtree {:?} with subtree {:?}", copy_a, copy_b);
                    todo!();

                    let node_a = *trees[ii].nodes.get(&i).unwrap();
                    let node_b = *trees[jj].nodes.get(&j).unwrap();

                    trees[ii].nodes.insert(i, node_b);
                    trees[jj].nodes.insert(j, node_a);
                } else {
                    let nodes_a = trees[ii].eject_subtree(i);
                    let nodes_b = trees[jj].eject_subtree(j);

                    for node in nodes_a {
                        trees[jj].insert_recur(j, node);
                    }
                    for node in nodes_b {
                        trees[ii].insert_recur(i, node);
                    }
                }
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
