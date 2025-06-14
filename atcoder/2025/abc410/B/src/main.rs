use proconio::input;
use std::{
    collections::BTreeSet,
    io::{BufWriter, Write, stdout},
};

fn ball_nums(n: usize, xs: &[usize]) -> Vec<usize> {
    let mut boxes: BTreeSet<(usize, usize)> = (1..=n).map(|i| (0, i)).collect();
    let mut result = Vec::with_capacity(xs.len());

    for &xi in xs.iter() {
        if xi == 0 {
            if let Some((k, i)) = boxes.pop_first() {
                boxes.insert((k + 1, i));
                result.push(i);
            } else {
                unreachable!();
            }
        } else {
            let el = *boxes.iter().find(|(_, i)| *i == xi).unwrap();
            boxes.remove(&el);

            let k = el.0;
            boxes.insert((k + 1, xi));
            result.push(xi);
        }
    }

    result
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        q: usize,
        xs: [usize; q],
    }

    let result = ball_nums(n, &xs)
        .into_iter()
        .map(|x| x.to_string())
        .collect::<Vec<_>>()
        .join(" ");
    writeln!(writer, "{}", result).unwrap();
    writer.flush().unwrap();
}
