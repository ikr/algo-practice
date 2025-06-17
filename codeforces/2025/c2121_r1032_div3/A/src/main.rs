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

fn min_steps(s: i64, xs: Vec<i64>) -> i64 {
    let lo = *xs.iter().min().unwrap();
    let hi = xs.into_iter().max().unwrap();

    if s <= lo {
        hi - s
    } else if hi <= s {
        s - lo
    } else {
        let d = hi - lo;
        (s - lo + d).min(hi - s + d)
    }
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let cases_num: u16 = scanner.next();

    for _ in 1..=cases_num {
        let n: usize = scanner.next();
        let s: i64 = scanner.next();
        let xs: Vec<i64> = scanner.next_n(n);

        let result = min_steps(s, xs);
        writeln!(writer, "{}", result).unwrap();
    }

    writer.flush().unwrap();
}
