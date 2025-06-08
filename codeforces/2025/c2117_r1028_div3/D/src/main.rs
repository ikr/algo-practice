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

fn can_explode(aa: Vec<i64>) -> bool {
    let n = aa.len() as i64;
    let a_1 = aa[0];
    let a_n = aa.last().unwrap();
    let xp = a_1 - a_n * n;
    let xq = 1 - n * n;

    if xp.abs() % xq.abs() != 0 {
        return false;
    }

    let x = xp / xq;
    if x < 0 {
        return false;
    }

    let y = a_n - x * n;
    if y < 0 {
        return false;
    }

    for (j, a) in aa.into_iter().enumerate() {
        let i: i64 = (j + 1) as i64;
        if a != x * i + y * (n - i + 1) {
            return false;
        }
    }

    true
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

        let result = can_explode(xs);
        writeln!(writer, "{}", if result { "YES" } else { "NO" }).unwrap();
    }

    writer.flush().unwrap();
}
