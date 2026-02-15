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

fn is_possible_to_sort(mut xs: Vec<usize>) -> bool {
    let n = xs.len();

    if !n.is_multiple_of(2) && xs[n / 2] != n / 2 + 1 {
        return false;
    }

    for p in 1..=n / 2 {
        let i = p - 1;
        let j = p * 2 - 1;

        if xs[i] > xs[j] {
            xs.swap(i, j);
        }
    }

    xs.is_sorted()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let cases_num: u16 = scanner.next();

    for _ in 1..=cases_num {
        let n: usize = scanner.next();
        let xs: Vec<usize> = scanner.next_n(n);

        let result = if is_possible_to_sort(xs) { "YES" } else { "NO" };
        writeln!(writer, "{result}").unwrap();
    }

    writer.flush().unwrap();
}
