use std::io::{self, stdin, BufWriter, Write};

#[derive(Default)]
struct Scanner {
    buffer: Vec<String>,
}

impl Scanner {
    fn next_string(&mut self) -> String {
        loop {
            if let Some(token) = self.buffer.pop() {
                return token;
            }
            let mut input = String::new();
            stdin().read_line(&mut input).expect("Failed read");
            self.buffer = input.split_whitespace().rev().map(String::from).collect();
        }
    }
}

fn solve(xs: String) -> i32 {
    let bs = xs.bytes().collect::<Vec<_>>();
    let n = bs.len();
    let mut dp: Vec<(i32, i32)> = vec![(0, 0); n];

    dp[0] = match bs[0] {
        b'L' => (-1, 0),
        b'R' => (0, 1),
        _ => (-1, 1),
    };

    for i in 1..n {
        let (a, b) = dp[i - 1];
        dp[i] = match bs[i] {
            b'L' => (a - 1, b - 1),
            b'R' => (a + 1, b + 1),
            _ => (a - 1, b + 1),
        };
    }

    let mut lo = 0;
    let mut hi = 0;
    for (a, b) in dp {
        lo = lo.min(a).min(b);
        hi = hi.max(a).max(b);
    }
    (lo - hi).abs() / 2
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let s: String = scanner.next_string();
    let result = solve(s);
    writeln!(writer, "{}", result).unwrap();

    writer.flush().unwrap();
}
