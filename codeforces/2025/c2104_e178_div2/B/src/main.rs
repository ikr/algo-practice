use std::io::{BufWriter, Write, stdin, stdout};

#[derive(Default)]
struct Scanner {
    buffer: Vec<String>,
}

impl Scanner {
    fn next<T: std::str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buffer.pop() {
                return token.parse().ok().expect("Failed parse");
            }
            let mut input = String::new();
            stdin().read_line(&mut input).expect("Failed read");
            self.buffer = input.split_whitespace().rev().map(String::from).collect();
        }
    }

    fn next_n<T: std::str::FromStr>(&mut self, n: usize) -> Vec<T> {
        let mut result: Vec<T> = Vec::with_capacity(n);
        for _ in 0..n {
            result.push(self.next());
        }
        result
    }
}

fn suffix_sums(xs: &[i64]) -> Vec<i64> {
    let n = xs.len();
    let mut result = xs.to_vec();
    for i in (0..n - 1).rev() {
        result[i] = xs[i] + result[i + 1];
    }
    result
}

fn prefix_maxes(xs: &[i64]) -> Vec<i64> {
    xs.iter().fold(Vec::with_capacity(xs.len()), |mut acc, x| {
        if let Some(x0) = acc.last() {
            acc.push(*x0.max(x));
        } else {
            acc.push(*x);
        }
        acc
    })
}

fn optimal_tail_sums(xs: Vec<i64>) -> Vec<i64> {
    let n = xs.len();
    let suff_su = suffix_sums(&xs);
    let pref_hi = prefix_maxes(&xs);
    let mut result = Vec::with_capacity(n);

    for k in 1..=n {
        let m = n - k;
        let to_push: i64 = if k == 1 {
            pref_hi[n - 1]
        } else if k == n {
            suff_su[0]
        } else {
            let o0 = suff_su[m];
            let o1 = suff_su[m + 1] + pref_hi[m];
            o0.max(o1)
        };
        result.push(to_push);
    }

    result
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let cases_num: u16 = scanner.next();

    for _ in 1..=cases_num {
        let n: usize = scanner.next();
        let xs: Vec<i64> = scanner.next_n(n);

        let result = optimal_tail_sums(xs);
        writeln!(
            writer,
            "{}",
            result
                .into_iter()
                .map(|x| x.to_string())
                .collect::<Vec<_>>()
                .join(" ")
        )
        .unwrap();
    }

    writer.flush().unwrap();
}
