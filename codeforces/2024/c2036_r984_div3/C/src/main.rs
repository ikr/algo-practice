use std::io::{self, stdin, BufWriter, Write};

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

fn contains_1100(xs: &[u8]) -> bool {
    let n = xs.len();
    for i in 3..n {
        if xs[(i - 3)..=i] == [1, 1, 0, 0] {
            return true;
        }
    }
    false
}

fn has_1100_around(xs: &[u8], i0: usize) -> bool {
    let n = xs.len();
    let lo = i0.checked_sub(10).unwrap_or(0);
    let hi = (i0 + 10).min(n - 1);
    contains_1100(&xs[lo..=hi])
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let cases_num: u16 = scanner.next();

    for _ in 1..=cases_num {
        let mut xs: Vec<u8> = scanner
            .next::<String>()
            .as_bytes()
            .iter()
            .map(|c| c - b'0')
            .collect();

        let q: u32 = scanner.next();
        for _ in 0..q {
            let i = scanner.next::<usize>() - 1;
            let v: u8 = scanner.next();
            xs[i] = v;
            let result = has_1100_around(&xs, i);
            writeln!(writer, "{}", if result { "YES" } else { "NO" }).unwrap();
        }
    }

    writer.flush().unwrap();
}
