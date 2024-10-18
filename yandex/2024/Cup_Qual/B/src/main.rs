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

fn solve(xs: &[i32]) -> u64 {
    let n = xs.len();

    let mut ltr = vec![0; n];
    for i in 1..n {
        ltr[i] = if xs[i - 1] < xs[i] { ltr[i - 1] + 1 } else { 0 };
    }

    let mut rtl = vec![0; n];
    for i in (0..(n - 1)).rev() {
        rtl[i] = if xs[i] > xs[i + 1] { rtl[i + 1] + 1 } else { 0 };
    }

    let mut result: u64 = 0;
    for i in 1..(n - 1) {
        result += ltr[i] * rtl[i];
    }
    result
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let cases_num: u8 = scanner.next();

    for _ in 1..=cases_num {
        let n: usize = scanner.next();
        let mut xs: Vec<i32> = vec![0; n];
        for x in xs.iter_mut() {
            *x = scanner.next();
        }

        let result = solve(&xs);
        writeln!(writer, "{}", result).unwrap();
    }

    writer.flush().unwrap();
}
