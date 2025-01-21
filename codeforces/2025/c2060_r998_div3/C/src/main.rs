use std::{
    collections::BTreeMap,
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

fn div_ceil(x: i32, y: i32) -> i32 {
    if x == 0 {
        0
    } else {
        1 + (x - 1) / y
    }
}

fn solve(xs: &[i32], k: i32) -> usize {
    let fq: BTreeMap<i32, usize> = xs.iter().fold(BTreeMap::new(), |mut acc, x| {
        acc.entry(*x).and_modify(|f| *f += 1).or_insert(1);
        acc
    });

    (0..div_ceil(k, 2)).fold(
        if k % 2 == 0 {
            if let Some(f) = fq.get(&(k / 2)) {
                f / 2
            } else {
                0
            }
        } else {
            0
        },
        |acc, p| {
            acc + if let Some(g) = fq.get(&(k - p)) {
                if let Some(f) = fq.get(&p) {
                    *g.min(f)
                } else {
                    0
                }
            } else {
                0
            }
        },
    )
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let cases_num: u16 = scanner.next();

    for _ in 1..=cases_num {
        let n: usize = scanner.next();
        let k: i32 = scanner.next();

        let mut xs: Vec<i32> = vec![0; n];
        for x in xs.iter_mut() {
            *x = scanner.next();
        }

        let result = solve(&xs, k);
        writeln!(writer, "{}", result).unwrap();
    }

    writer.flush().unwrap();
}
