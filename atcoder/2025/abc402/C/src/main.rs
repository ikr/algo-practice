use proconio::input;
use std::{
    collections::HashMap,
    io::{BufWriter, Write, stdout},
};

fn index(xs: &[u32]) -> HashMap<u32, usize> {
    xs.iter().enumerate().map(|(i, x)| (*x, i)).collect()
}

fn max_bindex(bidx: &HashMap<u32, usize>, a: &[u32]) -> usize {
    *a.iter().map(|a| bidx.get(a).unwrap()).max().unwrap()
}

fn prefix_sums(xs: &[usize]) -> Vec<usize> {
    xs.iter().fold(vec![], |mut acc, x| {
        if let Some(last) = acc.last() {
            acc.push(last + x);
        } else {
            acc.push(*x);
        }
        acc
    })
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        m: usize,
    }

    let mut aa: Vec<Vec<u32>> = vec![vec![]; m];

    for i in 0..m {
        input! {
            k: usize,
            a: [u32; k],
        }
        aa[i] = a;
    }

    input! { b: [u32; n] }
    let bidx = index(&b);
    let mut ys: Vec<usize> = vec![0; n];

    for a in aa.into_iter() {
        let i = max_bindex(&bidx, &a);
        ys[i] += 1;
    }

    for r in prefix_sums(&ys) {
        writeln!(writer, "{}", r).unwrap();
    }

    writer.flush().unwrap();
}
