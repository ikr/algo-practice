use std::io::{stdin, stdout, BufWriter, Write};

const M: i64 = 1_000_000_007;

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

fn div_ceil(a: i64, b: i64) -> i64 {
    (a + b - 1) / b
}

fn flaws_sum(mut m: i64, xs0: Vec<i64>) -> i64 {
    let mut xs = xs0.clone();
    todo!()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let m: i64 = scanner.next();
    let n: usize = scanner.next();
    let mut xs: Vec<i64> = scanner.next_n(n);
    xs.sort_by(|a, b| b.cmp(a));

    let result = flaws_sum(m, xs);
    writeln!(writer, "{result}").unwrap();

    writer.flush().unwrap();
}
