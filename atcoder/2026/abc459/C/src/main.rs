use proconio::{input, marker::Usize1};
use std::io::{BufWriter, Write, stdout};

struct DroppedFreqs {
    xs: Vec<usize>,
    fq: Vec<usize>,
    lo: usize,
}

impl DroppedFreqs {
    fn new(n: usize, q: usize) -> Self {
        Self {
            xs: vec![0; n],
            fq: vec![0; q + 1],
            lo: 0,
        }
    }

    fn inc_at(&mut self, i: usize) {
        self.xs[i] += 1;
        self.fq[self.xs[i]] += 1;

        if self.fq[self.xs[i]] == self.xs.len() {
            self.lo = self.xs[i];
        }
    }

    fn num_cells_at_least_k(&self, k: usize) -> usize {
        if k + self.lo >= self.fq.len() {
            0
        } else {
            self.fq[k + self.lo]
        }
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

    let mut dfs = DroppedFreqs::new(n, q);

    for (t, k) in queries {
        if t == 1 {
            dfs.inc_at(k);
        } else {
            assert_eq!(t, 2);
            let result = dfs.num_cells_at_least_k(k);
            writeln!(writer, "{result}").unwrap();
        }
    }

    writer.flush().unwrap();
}
