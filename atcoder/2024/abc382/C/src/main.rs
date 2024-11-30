use proconio::input;
use std::{
    collections::BTreeMap,
    io::{self, BufWriter, Write},
};

fn solve(people: &[i32], sushi: &[i32]) -> Vec<Option<usize>> {
    let person_index_by_taste: BTreeMap<i32, usize> =
        people
            .iter()
            .enumerate()
            .rev()
            .fold(BTreeMap::new(), |mut acc, (i, &t)| {
                acc.entry(t).and_modify(|j| *j = i).or_insert(i);
                acc
            });

    let mut result = vec![None; sushi.len()];

    for (i, &s) in sushi.iter().enumerate() {
        let r = person_index_by_taste.range(1..=s);
        if let Some((_, &j)) = r.into_iter().last() {
            result[i] = Some(j + 1);
        }
    }

    result
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        m: usize,
        people: [i32; n],
        sushi: [i32; m],
    }

    for mbi in solve(&people, &sushi) {
        if let Some(i) = mbi {
            writeln!(writer, "{}", i).unwrap();
        } else {
            writeln!(writer, "-1").unwrap();
        }
    }
    writer.flush().unwrap();
}
