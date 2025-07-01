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

fn prefix_mins(xs: &[u32]) -> Vec<u32> {
    xs.iter()
        .scan(u32::MAX, |cur, &x| {
            *cur = x.min(*cur);
            Some(*cur)
        })
        .collect()
}

fn prefix_maxes(xs: &[u32]) -> Vec<u32> {
    xs.iter()
        .scan(0, |cur, &x| {
            *cur = x.max(*cur);
            Some(*cur)
        })
        .collect()
}

fn possibilities(mut xs: Vec<u32>) -> Vec<bool> {
    let n = xs.len();
    let pref = prefix_mins(&xs);
    let lo = *pref.last().unwrap();

    xs.reverse();
    let mut suff = prefix_maxes(&xs);
    suff.reverse();
    xs.reverse();
    let hi = suff[0];

    xs.into_iter()
        .enumerate()
        .map(|(i, x)| {
            let lhs = if i == 0 { u32::MAX } else { pref[i - 1] };
            let rhs = if i == n - 1 { 0 } else { suff[i + 1] };
            x == lo || x == hi || pref[i].min(rhs) == x || suff[i].max(lhs) == x
        })
        .collect()
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

        let result: String = possibilities(xs)
            .into_iter()
            .map(|yes| if yes { '1' } else { '0' })
            .collect();
        writeln!(writer, "{result}").unwrap();
    }

    writer.flush().unwrap();
}
