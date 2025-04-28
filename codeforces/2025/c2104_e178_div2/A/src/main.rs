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
}

fn is_possible(a: i64, b: i64, c: i64) -> bool {
    let xx = b + c - 2 * a;
    if xx < 0 || xx % 3 != 0 {
        return false;
    }
    let x = xx / 3;
    let y = a + x - b;
    y >= 0
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let cases_num: u16 = scanner.next();

    for _ in 1..=cases_num {
        let a: i64 = scanner.next();
        let b: i64 = scanner.next();
        let c: i64 = scanner.next();

        let result = is_possible(a, b, c);
        writeln!(writer, "{}", if result { "YES" } else { "NO" }).unwrap();
    }

    writer.flush().unwrap();
}
