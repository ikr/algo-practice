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

fn max_value(mut xs: Vec<u32>) -> u32 {
    let (i0, _) = xs.iter().enumerate().max_by_key(|&(_, x)| x).unwrap();
    xs.swap(0, i0);

    let cum_maxes: Vec<u32> = xs
        .into_iter()
        .scan(0, |acc, x| {
            *acc = x.max(*acc);
            Some(*acc)
        })
        .collect();

    cum_maxes.into_iter().sum()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let cases_num: u16 = scanner.next();

    for _ in 1..=cases_num {
        let n: usize = scanner.next();
        let xs: Vec<u32> = scanner.next_n(n);

        let result = max_value(xs);
        writeln!(writer, "{result}").unwrap();
    }

    writer.flush().unwrap();
}
