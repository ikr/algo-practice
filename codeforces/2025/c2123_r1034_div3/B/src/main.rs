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

fn can_index_j_stay_among_k_last(mut xs: Vec<u32>, j: usize, k: usize) -> bool {
    let x0 = xs[j];
    xs.sort();
    xs.reverse();
    xs.dedup();

    let i0 = xs.into_iter().position(|x| x == x0).unwrap();
    i0 < k
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let cases_num: u16 = scanner.next();

    for _ in 1..=cases_num {
        let n: usize = scanner.next();
        let mut j: usize = scanner.next();
        j -= 1;
        let k = scanner.next();
        let xs: Vec<u32> = scanner.next_n(n);
        let result = can_index_j_stay_among_k_last(xs, j, k);
        writeln!(writer, "{}", if result { "YES" } else { "NO" }).unwrap();
    }

    writer.flush().unwrap();
}
