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

fn is_perfect_square(x: usize) -> bool {
    if x < 2 {
        return true;
    }

    let q = ((x as f64).sqrt()) as usize;
    q.pow(2) == x || (q - 1).pow(2) == x || (q + 1).pow(2) == x
}

fn is_possible(a: usize, b: usize) -> bool {
    if a + b == 0 {
        return false;
    }
    is_perfect_square(a + b)
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let cases_num: u16 = scanner.next();

    for _ in 1..=cases_num {
        let a: usize = scanner.next();
        let b: usize = scanner.next();

        let result = if is_possible(a, b) { "YES" } else { "NO" };
        writeln!(writer, "{result}").unwrap();
    }

    writer.flush().unwrap();
}
