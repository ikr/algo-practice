use std::{
    collections::HashMap,
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

fn solve(xs: &[u32], k: u32) -> u32 {
    let mut stash: HashMap<u32, usize> = HashMap::new();
    let mut pairs: u32 = 0;

    for &x in xs {
        let y = k.saturating_sub(x);
        if let Some(&f) = stash.get(&y) {
            if f != 0 {
                pairs += 1;
                stash.entry(y).and_modify(|g| *g -= 1);
            }
        } else {
            stash.entry(x).and_modify(|g| *g += 1).or_insert(1);
        }
    }

    pairs
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let cases_num: u16 = scanner.next();

    for _ in 1..=cases_num {
        let n: usize = scanner.next();
        let k: u32 = scanner.next();

        let mut xs: Vec<u32> = vec![0; n];
        for x in xs.iter_mut() {
            *x = scanner.next();
        }

        let result = solve(&xs, k);
        writeln!(writer, "{}", result).unwrap();
    }

    writer.flush().unwrap();
}
