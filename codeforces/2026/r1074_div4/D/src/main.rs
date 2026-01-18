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

fn apply_all_ops(h: u64, xs: Vec<u64>, ops: Vec<(usize, u64)>) -> Vec<u64> {
    eprintln!("h:{h} xs:{:?} ops:{:?}", xs, ops);
    todo!()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let cases_num: u16 = scanner.next();

    for _ in 1..=cases_num {
        let n: usize = scanner.next();
        let m: usize = scanner.next();
        let h: u64 = scanner.next();
        let xs: Vec<u64> = scanner.next_n(n);
        let mut ops: Vec<(usize, u64)> = Vec::with_capacity(m);

        for _ in 0..m {
            let bi: usize = scanner.next();
            let ci: u64 = scanner.next();
            ops.push((bi - 1, ci));
        }

        let result = apply_all_ops(h, xs, ops)
            .into_iter()
            .map(|x| x.to_string())
            .collect::<Vec<_>>()
            .join(" ");

        writeln!(writer, "{result}").unwrap();
    }

    writer.flush().unwrap();
}
