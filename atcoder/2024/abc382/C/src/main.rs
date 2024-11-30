use proconio::input;
use std::{
    collections::BTreeMap,
    io::{self, BufWriter, Write},
};

fn solve(people: &[i32], sushi: &[i32]) -> Vec<Option<usize>> {
    let mut person_index_by_taste: BTreeMap<i32, usize> = BTreeMap::new();
    for (i, &p) in people.iter().enumerate().rev() {
        let rk: Vec<i32> = person_index_by_taste.range(p..).map(|(&x, _)| x).collect();
        for k in rk {
            person_index_by_taste.remove(&k).unwrap();
        }
        person_index_by_taste.insert(p, i);
    }

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
