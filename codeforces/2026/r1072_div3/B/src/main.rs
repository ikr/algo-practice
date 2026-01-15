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

fn drain_time_after_vadim_left(s: i32, k: i32, m: i32) -> i32 {
    if s <= k {
        (s - (m % k)).max(0)
    } else {
        let sand = if (m / k) % 2 == 0 { s } else { k };
        (sand - (m % k)).max(0)
    }
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let cases_num: u16 = scanner.next();

    for _ in 1..=cases_num {
        let [s, k, m] = scanner.next_n(3).try_into().unwrap();
        let result = drain_time_after_vadim_left(s, k, m);
        writeln!(writer, "{result}").unwrap();
    }

    writer.flush().unwrap();
}
