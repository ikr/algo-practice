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
}

fn solve(n: u32) -> Vec<u32> {
    let mut pre: Vec<u32> = Vec::with_capacity((n / 2) as usize);
    let mut suf: Vec<u32> = Vec::with_capacity((n / 2) as usize);
    let iota: Vec<u32> = (1..=n).collect();

    for ab0 in iota.chunks(2) {
        let mut ab: Vec<u32> = ab0.to_vec();
        if let Some(b) = ab.pop() {
            suf.push(b);
        }
        if let Some(a) = ab.pop() {
            pre.push(a);
        }
    }
    suf.reverse();
    pre.extend(suf);
    pre
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let cases_num: u16 = scanner.next();

    for _ in 1..=cases_num {
        let n: u32 = scanner.next();
        let result = solve(n);
        let result_string = result
            .into_iter()
            .map(|x| x.to_string())
            .collect::<Vec<_>>()
            .join(" ");
        writeln!(writer, "{}", result_string).unwrap();
    }

    writer.flush().unwrap();
}
