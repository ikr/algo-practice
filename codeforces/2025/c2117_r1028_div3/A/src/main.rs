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

fn can_pass(d: usize, xs: Vec<u8>) -> bool {
    let maybe_i0 = xs.iter().position(|x| *x == 1);
    if let Some(i0) = maybe_i0 {
        !xs.iter().skip(i0 + d).any(|x| *x == 1)
    } else {
        true
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
        let d: usize = scanner.next();
        let xs: Vec<u8> = scanner.next_n(n);

        let result = can_pass(d, xs);
        writeln!(writer, "{}", if result { "YES" } else { "NO" }).unwrap();
    }

    writer.flush().unwrap();
}
