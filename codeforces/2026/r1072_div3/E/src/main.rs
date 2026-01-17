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

fn num_pairs(n: usize) -> usize {
    n * (n - 1) / 2
}

fn exquisite_interval_counts_by_k(xs: Vec<u32>) -> Vec<usize> {
    let ds: Vec<_> = xs.windows(2).map(|ab| ab[0].abs_diff(ab[1])).collect();
    let mut result = vec![0; xs.len()];
    let mut monostack: Vec<u32> = vec![];

    for d in ds {
        if let Some(&u) = monostack.last()
            && d < u
        {
            while let Some(u) = monostack.pop() {
                let m = monostack.len() + 1;
                result[u as usize] += num_pairs(m + 1);
            }
        }
        monostack.push(d);
    }

    while let Some(u) = monostack.pop() {
        let m = monostack.len() + 1;
        result[u as usize] += num_pairs(m + 1);
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
        let xs: Vec<u32> = scanner.next_n(n);

        let result = exquisite_interval_counts_by_k(xs)
            .into_iter()
            .skip(1)
            .map(|x| x.to_string())
            .collect::<Vec<_>>()
            .join(" ");

        writeln!(writer, "{result}").unwrap();
    }

    writer.flush().unwrap();
}
