use proconio::input;
use std::{
    collections::HashSet,
    io::{BufWriter, Write, stdout},
};

fn lit_len(mut x: u64) -> u32 {
    if x == 0 {
        return 1;
    }

    let mut result = 0;
    while x != 0 {
        x /= 10;
        result += 1;
    }
    result
}

fn lit_concat(a: u64, b: u64) -> u64 {
    let pb = lit_len(b);
    a * 10u64.pow(pb) + b
}

fn kth_smallest_good_inteter(k: usize) -> u64 {
    let mut xss: Vec<HashSet<u64>> = vec![HashSet::new(); 30];

    for e in 0..30 {
        let x = 2u64.pow(e);
        xss[lit_len(x) as usize].insert(x);
    }

    for l in 2..30 {
        for l1 in 1..l {
            let l2 = l - l1;
            assert_ne!(l2, 0);

            let mut addition: HashSet<u64> = HashSet::new();

            for &lhs in &xss[l1] {
                for &rhs in &xss[l2] {
                    let x = lit_concat(lhs, rhs);

                    if x <= 10u64.pow(9) {
                        addition.insert(x);
                    }
                }
            }

            xss[l].extend(addition);
        }
    }

    let mut xs: Vec<u64> = vec![];
    for ys in xss {
        xs.extend(ys);
    }
    xs[k + 1]
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        k: usize,
    }

    let result = kth_smallest_good_inteter(k);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn test_lit_len() {
        for (arg, res) in vec![
            (1, 1),
            (128, 3),
            (1001, 4),
            (9, 1),
            (2u64.pow(29), 9),
            (90000, 5),
            (0, 1),
        ] {
            assert_eq!(lit_len(arg), res);
        }
    }

    #[test]
    fn test_lit_concat() {
        for (a, b, res) in vec![
            (1, 1, 11),
            (123, 456, 123456),
            (100, 500, 100500),
            (1, 222, 1222),
            (1000, 1, 10001),
        ] {
            assert_eq!(lit_concat(a, b), res);
        }
    }
}
