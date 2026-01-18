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

fn streak_lengths(xs: Vec<i64>) -> Vec<usize> {
    let mut i0: usize = 0;
    let mut result = vec![];

    result
}

fn max_post_adjustment_mex(mut xs: Vec<i64>) -> i64 {
    xs.sort();
    xs.dedup();
    let ps: Vec<_> = xs.windows(2).map(|ab| (ab[0], ab[1])).collect();
    let mb_i0 = ps.into_iter().position(|(a, b)| a + 1 != b);

    if let Some(i0) = mb_i0 {
        (i0 + 1) as i64
    } else {
        xs.len() as i64
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
        let xs: Vec<i64> = scanner.next_n(n);

        let result = max_post_adjustment_mex(xs);
        writeln!(writer, "{result}").unwrap();
    }

    writer.flush().unwrap();
}
