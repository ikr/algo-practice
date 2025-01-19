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

fn solve(xss: &[Vec<u16>]) -> Option<Vec<usize>> {
    todo!()
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let cases_num: u16 = scanner.next();

    for _ in 1..=cases_num {
        let n: usize = scanner.next();
        let m: usize = scanner.next();

        let mut xss: Vec<Vec<u16>> = vec![vec![0; m]; n];
        for row in xss.iter_mut() {
            for x in row.iter_mut() {
                *x = scanner.next();
            }
        }

        if let Some(ii) = solve(&xss) {
            let result = ii
                .iter()
                .map(|i| (i + 1).to_string())
                .collect::<Vec<_>>()
                .join(" ");
            writeln!(writer, "{}", result).unwrap();
        } else {
            writeln!(writer, "-1").unwrap();
        }
    }

    writer.flush().unwrap();
}
