use std::io::{self, stdin, BufWriter, Write};

fn is_perfect(xs: &[i32]) -> bool {
    let n = xs.len();
    for i in 1..n {
        let d = xs[i].abs_diff(xs[i - 1]);
        if d != 5 && d != 7 {
            return false;
        }
    }
    true
}

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

fn solve(xs: &[i32]) -> i32 {
    xs.iter().sum::<i32>()
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let cases_num: u16 = scanner.next();

    for _ in 1..=cases_num {
        let n: usize = scanner.next();
        let mut xs: Vec<i32> = vec![0; n];
        for x in xs.iter_mut() {
            *x = scanner.next();
        }

        let result = is_perfect(&xs);
        writeln!(writer, "{}", if result { "YES" } else { "NO" }).unwrap();
    }

    writer.flush().unwrap();
}
