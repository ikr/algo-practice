use std::{
    collections::HashMap,
    io::{BufWriter, Write, stdin, stdout},
};

const INF: i32 = 1_000;

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

fn recur(memo: &mut HashMap<(i32, i32), i32>, n: i32, k: i32) -> i32 {
    if let Some(&v) = memo.get(&(n, k)) {
        v
    } else {
        let v = {
            if k < 0 {
                INF
            } else if k == 0 {
                0
            } else if n < k {
                INF
            } else if n == k {
                0
            } else {
                let n1 = n / 2;
                let n2 = n - n1;
                let o1 = 1 + recur(memo, n1, k);
                let o2 = 1 + recur(memo, n2, k);
                o1.min(o2)
            }
        };

        memo.insert((n, k), v);
        v
    }
}

fn min_ops(n: i32, k: i32) -> i32 {
    let mut memo: HashMap<(i32, i32), i32> = HashMap::new();
    recur(&mut memo, n, k)
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let cases_num: u16 = scanner.next();

    for _ in 1..=cases_num {
        let n = scanner.next();
        let k = scanner.next();

        let result = {
            let raw = min_ops(n, k);
            if raw >= INF { -1 } else { raw }
        };

        writeln!(writer, "{result}").unwrap();
    }

    writer.flush().unwrap();
}
