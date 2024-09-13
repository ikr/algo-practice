use std::collections::{HashSet, VecDeque};

use proconio::input;
use proconio::marker::Bytes;
use proconio_derive::fastout;

struct Graph {
    ins: Vec<u8>,
    outs: Vec<u8>,
}

impl Graph {
    fn vertices_num(&self) -> usize {
        self.ins.len()
    }

    fn adjacent(&self, u: usize) -> Vec<usize> {
        if self.outs[u] == b'N' {
            vec![]
        } else {
            let mut vs: Vec<usize> = vec![];
            if u != 0 {
                vs.push(u - 1);
            }
            if u != self.vertices_num() - 1 {
                vs.push(u + 1);
            }

            vs.into_iter().filter(|v| self.ins[*v] == b'Y').collect()
        }
    }

    fn reachable_from_u0(&self, u0: usize) -> HashSet<usize> {
        let mut result: HashSet<usize> = HashSet::new();
        result.insert(u0);

        let mut q: VecDeque<usize> = VecDeque::new();
        q.push_back(u0);

        while let Some(u) = q.pop_front() {
            for v in self.adjacent(u) {
                if !result.contains(&v) {
                    result.insert(v);
                    q.push_back(v);
                }
            }
        }

        result
    }
}

fn solve(g: &Graph) -> Vec<Vec<u8>> {
    let n = g.vertices_num();
    let mut result = vec![vec![b'N'; n]; n];

    for (u0, row) in result.iter_mut().enumerate() {
        for v in g.reachable_from_u0(u0) {
            row[v] = b'Y';
        }
    }
    result
}

#[fastout]
fn main() {
    input! {
        cases_num: u16,
    }

    for t in 1..=cases_num {
        input! {
            n: usize,
            ins: Bytes,
            outs: Bytes,
        }

        assert_eq!(ins.len(), n);
        assert_eq!(outs.len(), n);

        println!("Case #{}:", t);
        for row in solve(&Graph { ins, outs }) {
            println!("{}", std::str::from_utf8(&row).unwrap());
        }
    }
}
