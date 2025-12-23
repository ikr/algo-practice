use std::io::{stdin, stdout, BufWriter, Write};

const PRIMES: [u64; 15] = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47];

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

fn artefacts_count(a: u64, b: u64) -> usize {
    todo!()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);
    let mut scanner = Scanner::default();

    let q: u16 = scanner.next();
    for _ in 0..q {
        let a: u64 = scanner.next();
        let b: u64 = scanner.next();
        let result = artefacts_count(a, b);
        writeln!(writer, "{result}").unwrap();
    }

    writer.flush().unwrap();
}
