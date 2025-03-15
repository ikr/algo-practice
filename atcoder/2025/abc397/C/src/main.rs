use itertools::Itertools;
use proconio::input;
use std::{
    collections::{HashMap, HashSet},
    io::{self, BufWriter, Write},
};

fn solve(xs: &[i32]) -> usize {
    let n = xs.len();
    let mut ls: HashSet<i32> = HashSet::new();
    let mut rc: HashMap<i32, usize> = xs.iter().copied().counts();

    let mut result: usize = 0;
    for &x in xs[..n - 1].iter() {
        ls.insert(x);

        rc.entry(x).and_modify(|f| *f -= 1);
        if let Some(f) = rc.get(&x) {
            if *f == 0 {
                rc.remove(&x);
            }
        }

        result = result.max(ls.len() + rc.len());
    }
    result
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        xs: [i32; n],
    }

    let result = solve(&xs);
    writeln!(writer, "{}", result).unwrap();
    writer.flush().unwrap();
}
