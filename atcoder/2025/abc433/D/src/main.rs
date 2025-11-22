use proconio::input;
use std::{
    collections::HashMap,
    io::{BufWriter, Write, stdout},
};

fn digits_num(x: i64) -> i64 {
    assert!(x >= 0);
    if x == 0 { 1 } else { x.ilog10() as i64 + 1 }
}

fn proper_pairs_num(m: i64, xs: Vec<i64>) -> usize {
    let mut fq: Vec<HashMap<i64, usize>> = vec![HashMap::new(); 12];

    for &x in &xs {
        let q = digits_num(x) as usize;
        fq[q].entry(x % m).and_modify(|f| *f += 1).or_insert(1);
    }

    let mut result = 0;

    for a in xs {
        for q in 1..11 {
            let mut b: i64 = ((-a % m) + m) % m;
            b *= 10i64.pow(q as u32) % m;
            b %= m;
            assert!(b >= 0);
            result += *fq[q].get(&b).unwrap_or(&0);
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
        m: i64,
        xs: [i64; n],
    }

    let result = proper_pairs_num(m, xs);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_digits_num() {
        assert_eq!(digits_num(0), 1);
        assert_eq!(digits_num(1), 1);
        assert_eq!(digits_num(10), 2);
        assert_eq!(digits_num(99), 2);
        assert_eq!(digits_num(777), 3);
        assert_eq!(digits_num(200_000), 6);
    }
}
