use std::{
    collections::{BinaryHeap, HashMap},
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

fn max_revenue(n: u32, bottles: &[(u32, u32)]) -> u32 {
    let total_cost_by_brand: HashMap<u32, u32> =
        bottles.into_iter().fold(HashMap::new(), |mut acc, (b, c)| {
            acc.entry(*b).and_modify(|sub| *sub += c).or_insert(*c);
            acc
        });

    let mut h: BinaryHeap<u32> =
        total_cost_by_brand
            .into_iter()
            .fold(BinaryHeap::new(), |mut acc, (_, sub)| {
                acc.push(sub);
                acc
            });

    let mut result = 0;
    for _ in 0..n {
        if let Some(sub) = h.pop() {
            result += sub;
        } else {
            break;
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

    for _ in 1..=cases_num {
        let n: u32 = scanner.next();
        let k: usize = scanner.next();

        let mut xs: Vec<(u32, u32)> = vec![(0, 0); k];
        for (b, c) in xs.iter_mut() {
            *b = scanner.next();
            *c = scanner.next();
        }

        let result = max_revenue(n, &xs);
        writeln!(writer, "{}", result).unwrap();
    }

    writer.flush().unwrap();
}
