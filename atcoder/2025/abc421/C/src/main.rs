use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn run_length_encoding(xs: Vec<u8>) -> Vec<(usize, u8)> {
    assert!(!xs.is_empty());
    let mut result: Vec<(usize, u8)> = vec![(1, *xs.first().unwrap())];
    for x in xs.iter().skip(1) {
        if *x == result.last().unwrap().1 {
            result.last_mut().unwrap().0 += 1;
        } else {
            result.push((1, *x));
        }
    }
    result
}

fn min_ops(xs: Vec<u8>) -> usize {
    let mut q: Vec<usize> = run_length_encoding(xs)
        .into_iter()
        .map(|(l, _)| l)
        .collect();

    let mut result = 0;
    eprintln!("result:{result} q:{:?}", q);
    while let Some(b) = q.pop() {
        if let Some(a) = q.pop() {
            eprintln!("a:{a} b:{b}");
            if !(a == 1 && b == 1) {
                if b == 1 {
                    result += 1;
                    q.push(a - 1);
                } else if a == 1 {
                    result += b - 1;
                    let pre_b = q.pop().unwrap_or(0);
                    q.push(pre_b + b - 1);
                } else if a == b {
                    let k = a - 1;
                    result += k * (k + 1) / 2;
                } else if a < b {
                    let hi = b - 1;
                    let lo = hi - a + 1;
                    result += a * (hi + lo) / 2;
                    let pre_b = q.pop().unwrap_or(0);
                    q.push(pre_b + b - a);
                } else {
                    assert!(a > b);
                    let k = b - 1;
                    result += k * (k + 1) / 2;
                    q.push(a - b);
                }
            }
        } else {
            assert_eq!(b, 1);
            eprintln!("b:{b}");
        }
        eprintln!("result:{result} q:{:?}", q);
    }
    result
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        s: String,
    }
    assert_eq!(s.len(), 2 * n);

    let result = min_ops(
        s.chars()
            .map(|c| if c == 'A' { 0 } else { 1 })
            .collect::<Vec<_>>(),
    );
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
