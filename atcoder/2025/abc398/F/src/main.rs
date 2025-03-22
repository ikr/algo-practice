use proconio::input;
use std::io::{self, BufWriter, Write};

fn reversed(xs: &[char]) -> Vec<char> {
    let mut result = xs.to_vec();
    result.reverse();
    result
}

fn build_zz(xs: &[char], ys: &[char]) -> Vec<usize> {
    assert_eq!(xs.len(), ys.len());
    let n = xs.len();
    let mut z: Vec<usize> = vec![0; n];
    let mut l: usize = 0;
    let mut r: usize = 0;

    for i in 1..n {
        if i < r {
            z[i] = (r - i).min(z[i - l]);
        }

        while i + z[i] < n && ys[z[i]] == xs[i + z[i]] {
            z[i] += 1;
        }

        if i + z[i] > r {
            l = i;
            r = i + z[i];
        }
    }

    z
}

fn solve(xs: &[char]) -> String {
    let ys = reversed(xs);
    if xs == ys {
        return xs.iter().collect();
    }

    let z = build_zz(xs, &ys);
    for i in 1..xs.len() {
        let suff_len = xs.len() - i;
        if z[i] == suff_len {
            let mut s: String = xs.iter().collect();
            let mut t: Vec<char> = xs[..i].to_vec();
            t.reverse();
            s.extend(t);
            return s;
        }
    }
    panic!("Not found")
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        s: String,
    }

    let xs: Vec<char> = s.chars().collect();
    let result = solve(&xs);
    writeln!(writer, "{}", result).unwrap();
    writer.flush().unwrap();
}
