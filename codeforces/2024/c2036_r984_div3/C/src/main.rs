use std::{
    collections::HashSet,
    io::{self, stdin, BufWriter, Write},
};

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

fn all_1100_positions(xs: &[u8]) -> Vec<usize> {
    let mut result: Vec<usize> = vec![];
    let n = xs.len();
    for i in 3..n {
        if xs[(i - 3)..=i] == [1, 1, 0, 0] {
            result.push(i - 3);
        }
    }
    result
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let cases_num: u16 = scanner.next();

    for _ in 0..cases_num {
        let mut xs: Vec<u8> = scanner
            .next::<String>()
            .as_bytes()
            .iter()
            .map(|c| c - b'0')
            .collect();
        let n = xs.len();

        let mut idx: HashSet<usize> = all_1100_positions(&xs).into_iter().collect();

        let q: u32 = scanner.next();
        for _ in 0..q {
            let i = scanner.next::<usize>() - 1;
            let v: u8 = scanner.next();
            xs[i] = v;

            for di in 0..=8 {
                idx.remove(&i.saturating_sub(di));
                idx.remove(&(i + di));
            }

            let lo = i.saturating_sub(8);
            let hi = (i + 8).min(n - 1);
            for j in all_1100_positions(&xs[lo..=hi]) {
                idx.insert(lo + j);
            }

            let contains = !idx.is_empty();
            writeln!(writer, "{}", if contains { "YES" } else { "NO" }).unwrap();
        }
    }

    writer.flush().unwrap();
}
