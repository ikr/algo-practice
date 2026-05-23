use itertools::Itertools;
use proconio::input;
use proconio::marker::Bytes;
use std::io::{BufWriter, Write, stdout};

fn cum_sum(xs: Vec<usize>) -> Vec<usize> {
    xs.into_iter()
        .scan(0, |acc, x| {
            *acc += x;
            Some(*acc)
        })
        .collect()
}

fn byte_id(x: u8) -> usize {
    let spans: Vec<usize> = vec![3, 3, 3, 3, 3, 4, 3, 4];
    let cs = cum_sum(spans);
    let x0 = ((x - b'a') + 1) as usize;
    cs.into_iter().position(|a| a >= x0).unwrap() + 2
}

fn ids_of_firsts(ss: Vec<Vec<u8>>) -> Vec<usize> {
    ss.into_iter().map(|s| byte_id(s[0])).collect()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        ss: [Bytes; n],
    }

    let result = ids_of_firsts(ss).into_iter().join("");
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
