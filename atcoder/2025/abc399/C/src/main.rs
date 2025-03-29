use proconio::input;
use std::{
    collections::{HashMap, VecDeque},
    io::{BufWriter, Write, stdout},
};

fn solve(xs: &[u32]) -> usize {
    let mut idx: HashMap<(u32, u32), VecDeque<usize>> = xs
        .windows(2)
        .enumerate()
        .filter(|(_, ab)| ab[0] != ab[1])
        .map(|(i, ab)| (i, ab[0], ab[1]))
        .fold(HashMap::new(), |mut acc, (i, a, b)| {
            acc.entry((a, b))
                .and_modify(|ii| {
                    ii.push_back(i);
                })
                .or_insert(VecDeque::from([i]));
            acc
        });

    let mut result: usize = 0;

    for (_, a0, b0) in xs
        .windows(2)
        .enumerate()
        .map(|(i, ab)| (i, ab[0], ab[1]))
        .filter(|(_, x, y)| x != y)
    {
        for (a, b) in [(a0, b0), (b0, a0)] {
            idx.entry((a, b))
                .and_modify(|ii| {
                    ii.pop_front();
                })
                .or_default();

            if let Some(_) = idx.get_mut(&(a, b)).unwrap().pop_front() {
                result += 1;
                break;
            }
        }
    }

    result
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        t: usize
    }

    for _ in 0..t {
        input! {
            n: usize,
            xs: [u32; 2 * n],
        }

        let result = solve(&xs);
        writeln!(writer, "{}", result).unwrap();
    }

    writer.flush().unwrap();
}
