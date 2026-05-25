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

        if self.freqs.sum(..=self.drops) == 0 {
            self.drops += 1;
        }
    }

    fn num_cells_at_least_k(&self, k: usize) -> usize {
        self.xs.iter().filter(|&x| *x >= k + self.drops).count()
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
