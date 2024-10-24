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

fn winner_index(n: i32) -> usize {
    let mut cur = 0i32;
    let mut i = 1;
    loop {
        if cur.abs() > n {
            break;
        }
        let sign = if i % 2 == 0 { 1 } else { -1 };
        cur += sign * (2 * i - 1);
        i += 1;
    }

    (i % 2) as usize
}

fn main() {
    let players = ["Sakurako", "Kosuke"];
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let cases_num: u16 = scanner.next();

    for _ in 1..=cases_num {
        let n: i32 = scanner.next();
        let i = winner_index(n);
        writeln!(writer, "{}", players[i]).unwrap();
    }

    writer.flush().unwrap();
}
