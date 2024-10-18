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
    let known_drift = xs.bytes().fold(0, |acc, x| match x {
        b'L' => acc - 1,
        b'R' => acc + 1,
        _ => acc,
    });

    let mut lo: i32 = 0;
    let mut hi: i32 = 0;
    let mut cur: i32 = 0;

    for x in xs.bytes() {
        match x {
            b'L' => cur += 1,
            b'R' => cur -= 1,
            _ => {
                if known_drift <= 0 {
                    cur -= 1;
                } else {
                    cur += 1;
                }
            }
        }

        lo = lo.min(cur);
        hi = hi.max(cur);
    }

    (lo - hi).abs()
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
