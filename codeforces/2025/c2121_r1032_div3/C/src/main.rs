use std::{
    collections::{BTreeSet, HashSet},
    io::{BufWriter, Write, stdin, stdout},
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

    fn next_n<T: std::str::FromStr>(&mut self, n: usize) -> Vec<T> {
        let mut result: Vec<T> = Vec::with_capacity(n);
        for _ in 0..n {
            result.push(self.next());
        }
        result
    }
}

fn cross_coverable(ps: HashSet<(usize, usize)>) -> bool {
    {
        let mut qs: BTreeSet<_> = ps.iter().cloned().collect();
        let (i0, _) = qs.pop_first().unwrap();
        qs = qs.into_iter().filter(|(i, _)| *i != i0).collect();

        if let Some((_, j0)) = qs.pop_first() {
            if qs.into_iter().all(|(_, j)| j == j0) {
                return true;
            }
        } else {
            return true;
        }
    }

    {
        let mut qs: BTreeSet<_> = ps.iter().cloned().collect();
        let (_, j0) = qs.pop_first().unwrap();
        qs = qs.into_iter().filter(|(_, j)| *j != j0).collect();

        if let Some((i0, _)) = qs.pop_first() {
            qs.into_iter().all(|(i, _)| i == i0)
        } else {
            true
        }
    }
}

fn min_max_element(xss: Vec<Vec<u8>>) -> u8 {
    let hi = *xss
        .iter()
        .map(|row| row.iter().max().unwrap())
        .max()
        .unwrap();

    let mut ps: HashSet<(usize, usize)> = HashSet::new();
    for (i, row) in xss.into_iter().enumerate() {
        for (j, x) in row.into_iter().enumerate() {
            if x == hi {
                ps.insert((i, j));
            }
        }
    }
    if cross_coverable(ps) { hi - 1 } else { hi }
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
        let mut xss: Vec<Vec<u8>> = Vec::with_capacity(n);
        for _ in 0..n {
            let row: Vec<u8> = scanner.next_n(m);
            xss.push(row);
        }

        let result = min_max_element(xss);
        writeln!(writer, "{}", result).unwrap();
    }

    writer.flush().unwrap();
}
