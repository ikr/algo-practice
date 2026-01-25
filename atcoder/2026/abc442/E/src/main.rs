use proconio::{input, marker::Usize1};
use std::cmp::Ordering;
use std::io::{BufWriter, Write, stdout};

fn iof(x: bool) -> i64 {
    if x { 1 } else { 0 }
}

#[derive(Clone, Copy)]
struct Angle {
    x: i64,
    y: i64,
}

impl Angle {
    fn from(xy: (i64, i64)) -> Self {
        let (x, y) = xy;
        Self { x, y }
    }

    fn half(self) -> i64 {
        assert!(self.x != 0 || self.y != 0);
        iof(self.y < 0 || (self.y == 0 && self.x < 0))
    }

    fn is_less(self, other: Self) -> bool {
        let a = self;
        let b = other;
        (a.half(), a.y * b.x) < (b.half(), a.x * b.y)
    }

    fn cmp(self, other: Self) -> Ordering {
        if self.is_less(other) {
            Ordering::Less
        } else if other.is_less(self) {
            Ordering::Greater
        } else {
            Ordering::Equal
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
        ps: [(i64, i64); n],
        ij: [(Usize1, Usize1); q],
    }

    let angles: Vec<Angle> = ps.into_iter().map(Angle::from).collect();
    let mut sweep: Vec<usize> = (0..n).collect();
    sweep.sort_by(|&i, &j| angles[j].cmp(angles[i]));

    let idx: Vec<usize> = sweep
        .iter()
        .enumerate()
        .fold(vec![0; n], |mut acc, (seq, &i)| {
            acc[i] = seq;
            acc
        });

    let mut lmost_idx: Vec<usize> = idx.clone();
    let mut rmost_idx: Vec<usize> = idx.clone();

    for seq in 1..n {
        if angles[sweep[seq]].cmp(angles[sweep[seq - 1]]) == Ordering::Equal {
            lmost_idx[sweep[seq]] = lmost_idx[sweep[seq - 1]];
        }
    }

    for seq in (0..n - 1).rev() {
        if angles[sweep[seq]].cmp(angles[sweep[seq + 1]]) == Ordering::Equal {
            rmost_idx[sweep[seq]] = rmost_idx[sweep[seq + 1]];
        }
    }

    eprintln!(
        "sweep:{:?} idx:{:?} lmost:{:?} rmost:{:?}",
        sweep, idx, lmost_idx, rmost_idx
    );

    for (i, j) in ij {
        let ii = idx[i];
        let jj = idx[j];

        let result = if ii <= jj {
            rmost_idx[j] - lmost_idx[i] + 1
        } else {
            n - lmost_idx[i] + rmost_idx[j] + 1
        };
        writeln!(writer, "{result}").unwrap();
    }

    writer.flush().unwrap();
}
