use std::{
    cmp::Reverse,
    collections::BinaryHeap,
    io::{stdin, stdout, BufWriter, Write},
};

#[derive(Clone, Copy, Debug)]
struct Crd([i32; 3]);

impl Crd {
    fn effort_to(self, o: Crd) -> u32 {
        self.0
            .iter()
            .zip(o.0)
            .map(|(a, b)| a.abs_diff(b))
            .min()
            .unwrap()
    }
}

#[derive(Default)]
struct Scanner {
    buffer: Vec<String>,
}

impl Scanner {
    fn next<T: std::str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buffer.pop() {
                return token.parse().ok().expect("Failed parse");
            }
            let mut input = String::new();
            stdin().read_line(&mut input).expect("Failed read");
            self.buffer = input.split_whitespace().rev().map(String::from).collect();
        }
    }

    fn next_n<T: std::str::FromStr>(&mut self, n: usize) -> Vec<T> {
        let mut result: Vec<T> = Vec::with_capacity(n);
        for _ in 0..n {
            result.push(self.next());
        }
        result
    }

    fn next_n_crds(&mut self, n: usize) -> Vec<Crd> {
        let mut result: Vec<Crd> = Vec::with_capacity(n);
        for _ in 0..n {
            let xyz: [i32; 3] = self.next_n(3).try_into().unwrap();
            result.push(Crd(xyz));
        }
        result
    }
}

// https://github.com/kenkoooo/competitive-programming-rs/blob/master/src/data_structure/union_find.rs
pub struct UnionFind {
    parent: Vec<usize>,
    sizes: Vec<usize>,
    size: usize,
}

impl UnionFind {
    pub fn new(n: usize) -> UnionFind {
        UnionFind {
            parent: (0..n).collect::<Vec<usize>>(),
            sizes: vec![1; n],
            size: n,
        }
    }

    pub fn find(&mut self, x: usize) -> usize {
        if x == self.parent[x] {
            x
        } else {
            let px = self.parent[x];
            self.parent[x] = self.find(px);
            self.parent[x]
        }
    }

    pub fn unite(&mut self, x: usize, y: usize) -> bool {
        let parent_x = self.find(x);
        let parent_y = self.find(y);
        if parent_x == parent_y {
            return false;
        }

        let (large, small) = if self.sizes[parent_x] < self.sizes[parent_y] {
            (parent_y, parent_x)
        } else {
            (parent_x, parent_y)
        };

        self.parent[small] = large;
        self.sizes[large] += self.sizes[small];
        self.sizes[small] = 0;
        self.size -= 1;
        true
    }
}

fn min_total_effort(ps: Vec<Crd>) -> u64 {
    let n = ps.len();
    let mut idx: Vec<Vec<usize>> = vec![(0..n).collect::<Vec<_>>(); 3];
    for (k, sub) in idx.iter_mut().enumerate() {
        sub.sort_by_key(|&i| ps[i].0[k])
    }

    let mut q: BinaryHeap<(Reverse<u32>, usize, usize)> = BinaryHeap::new();
    for (k, sub) in idx.iter().enumerate() {
        for ij in sub.windows(2) {
            let [i, j] = ij.try_into().unwrap();
            q.push((Reverse(ps[i].0[k].abs_diff(ps[j].0[k])), i, j));
        }
    }

    let mut result = 0;
    let mut dsu = UnionFind::new(n);

    while let Some((_, i, j)) = q.pop() {
        if dsu.find(i) != dsu.find(j) {
            result += ps[i].effort_to(ps[j]) as u64;
            dsu.unite(i, j);
        }
    }

    result
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let n: usize = scanner.next();
    let xs: Vec<Crd> = scanner.next_n_crds(n);

    let result = min_total_effort(xs);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
