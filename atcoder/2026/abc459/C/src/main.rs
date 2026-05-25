use ac_library::fenwicktree::FenwickTree;
use proconio::{input, marker::Usize1};
use std::io::{BufWriter, Write, stdout};

const UB: usize = 300_001;

struct DroppedFreqs {
    xs: Vec<usize>,
    drops: usize,
    freqs: FenwickTree<i64>,
}

impl DroppedFreqs {
    fn new(n: usize) -> Self {
        let mut freqs = FenwickTree::new(UB, 0);
        freqs.add(0, n as i64);

        Self {
            xs: vec![0; n],
            drops: 0,
            freqs,
        }
    }

    fn inc_at(&mut self, i: usize) {
        let cur = self.xs[i];
        self.freqs.add(cur, -1);

        self.xs[i] += 1;
        self.freqs.add(cur + 1, 1);

        todo!();
    }

    fn num_cells_at_least_k(&self, k: usize) -> i64 {
        let level = (k + self.drops).min(UB);
        self.freqs.sum(level..)
    }
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        q: usize,
        queries:[(u8, Usize1); q],
    }

    let mut dfs = DroppedFreqs::new(n);

    for (t, x) in queries {
        if t == 1 {
            dfs.inc_at(x);
        } else {
            assert_eq!(t, 2);
            let result = dfs.num_cells_at_least_k(x);
            writeln!(writer, "{result}").unwrap();
        }
    }

    writer.flush().unwrap();
}
