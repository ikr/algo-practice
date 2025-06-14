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

    fn insert_recur(&mut self, i0: usize, node: Node) {
        if let Some(node0) = self.nodes.get(&i0) {
            let i1 = if node.0 < node0.0 { i0 * 2 } else { i0 * 2 + 1 };
            self.insert_recur(i1, node);
        } else {
            self.nodes.insert(i0, node);
        }
    }

    fn level_strings(&self, i0: usize) -> Vec<String> {
        let mut result = vec![String::new(); LEVEL_LIM];
        let mut q: VecDeque<usize> = VecDeque::from([i0]);

        while let Some(i) = q.pop_front() {
            let l = ilog2(i);
            result[l].push(self.nodes.get(&i).unwrap().1);

            for j in [i * 2, i * 2 + 1] {
                if self.nodes.contains_key(&j) {
                    q.push_back(j);
                }
            }
        }

        result
    }

    fn longest_level_string(&self, i0: usize) -> String {
        self.level_strings(i0)
            .into_iter()
            .enumerate()
            .max_by_key(|(level, s)| (s.len(), -(*level as i8)))
            .unwrap()
            .1
    }

    fn find_rank(&self, r: u16) -> usize {
        *self.nodes.iter().find(|(_, node)| node.0 == r).unwrap().0
    }

    fn eject_subtree(&mut self, i0: usize) -> Tree {
        assert!(self.nodes.contains_key(&i0));
        let mut result = Tree::new();
        let mut q: VecDeque<(usize, usize)> = VecDeque::from([(i0, 1)]);

        while let Some((i, ii)) = q.pop_front() {
            let node = *self.nodes.get(&i).unwrap();
            result.nodes.insert(ii, node);
            self.nodes.remove(&i);

            for (j, jj) in [(i * 2, ii * 2), (i * 2 + 1, ii * 2 + 1)] {
                if self.nodes.contains_key(&j) {
                    q.push_back((j, jj));
                }
            }
        }

        result
    }

    fn adopt_subtree(&mut self, i0: usize, other: Tree) {
        let mut q: VecDeque<(usize, usize)> = VecDeque::from([(1, i0)]);

        while let Some((i, ii)) = q.pop_front() {
            assert!(other.nodes.contains_key(&i));
            let node = *other.nodes.get(&i).unwrap();

            assert!(!self.nodes.contains_key(&ii));
            self.nodes.insert(ii, node);

            for (j, jj) in [(i * 2, ii * 2), (i * 2 + 1, ii * 2 + 1)] {
                if other.nodes.contains_key(&j) {
                    q.push_back((j, jj));
                }
            }
        }
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
    let mut tree = Tree::new();
    tree.nodes.insert(1, Node(0, '/'));

    for cmd in commands {
        match cmd {
            Cmd::Add(left_tree_node, right_tree_node) => {
                tree.insert_recur(2, left_tree_node);
                tree.insert_recur(3, right_tree_node);
                tangled_ranks.push((left_tree_node.0, right_tree_node.0));
            }
            Cmd::Swap(id) => {
                let (rank_a, rank_b) = tangled_ranks[id];
                let i = tree.find_rank(rank_a);
                let j = tree.find_rank(rank_b);

                let subtree_a = tree.eject_subtree(i);
                let subtree_b = tree.eject_subtree(j);

                tree.adopt_subtree(i, subtree_b);
                tree.adopt_subtree(j, subtree_a);
            }
        }
    }

    let result = [2, 3]
        .into_iter()
        .map(|i| tree.longest_level_string(i))
        .collect::<Vec<_>>()
        .join("");
    println!("{}", result);
}
