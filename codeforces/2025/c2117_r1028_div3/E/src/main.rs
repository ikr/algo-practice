use std::{
    collections::HashSet,
    io::{BufWriter, Write, stdin, stdout},
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

    fn next_n<T: std::str::FromStr>(&mut self, n: usize) -> Vec<T> {
        let mut result: Vec<T> = Vec::with_capacity(n);
        for _ in 0..n {
            result.push(self.next());
        }
        result
    }
}

fn max_matches(a: &[u32], b: &[u32]) -> usize {
    let n = a.len();
    let mut avs: HashSet<u32> = HashSet::new();
    let mut result = if a[0] == b[0] { 1 } else { 0 };

    for i in (1..n).rev() {
        if a[i] == b[i] {
            result = result.max(i + 1);
        }
        {
            let (cur, opp) = if (n - 1) % 2 == i % 2 {
                (a[i], a[i - 1])
            } else {
                (b[i], b[i - 1])
            };

            avs.insert(cur);
            if avs.contains(&opp) {
                result = result.max(i);
            }
        }
        if i > 1 {
            let (cur, opp) = if (n - 1) % 2 != i % 2 {
                (a[i], a[i - 2])
            } else {
                (b[i], b[i - 2])
            };

            avs.insert(cur);
            if avs.contains(&opp) {
                result = result.max(i - 1);
            }
        }
    }
    result
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let cases_num: u16 = scanner.next();

    for _ in 1..=cases_num {
        let n: usize = scanner.next();
        let a: Vec<u32> = scanner.next_n(n);
        let b: Vec<u32> = scanner.next_n(n);

        let result = max_matches(&a, &b).max(max_matches(&b, &a));
        writeln!(writer, "{}", result).unwrap();
    }

    writer.flush().unwrap();
}
