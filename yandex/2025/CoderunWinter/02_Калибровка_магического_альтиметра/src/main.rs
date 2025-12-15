use std::io::{stdin, stdout, BufWriter, Write};

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

fn bits_indices(bits: u16) -> Vec<usize> {
    let mut result = vec![];
    for i in 0..u16::BITS {
        if bits & (1 << i) != 0 {
            result.push(i as usize);
        }
    }
    result
}

fn get_all(xs: &[i16], indices: Vec<usize>) -> Vec<i16> {
    indices.into_iter().map(|i| xs[i]).collect()
}

fn min_sum(xs: Vec<i16>) -> i16 {
    let n = xs.len();

    let ss: Vec<i16> = (1u16..(1 << n))
        .map(|bits| get_all(&xs, bits_indices(bits)).into_iter().sum::<i16>())
        .collect();

    ss.into_iter()
        .min_by_key(|s| (s.abs_diff(100), -s))
        .unwrap()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let xs: Vec<i16> = scanner.next_n(10);

    let result = min_sum(xs);
    writeln!(writer, "{result}").unwrap();

    writer.flush().unwrap();
}
