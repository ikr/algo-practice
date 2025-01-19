use std::io::{self, stdin, BufWriter, Write};

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

fn is_sorted(xs: &[u16]) -> bool {
    xs.windows(2).all(|ab| ab[0] < ab[1])
}

fn solve(mut xss: Vec<Vec<u16>>) -> Option<Vec<usize>> {
    for row in xss.iter_mut() {
        row.sort();
    }

    let n = xss.len();
    let m = xss[0].len();
    let mut ii: Vec<usize> = (0..n).collect();
    ii.sort_by_key(|i| xss[*i][0]);

    let col = |j: usize| -> Vec<u16> {
        let mut result = vec![];
        for &i in ii.iter() {
            result.push(xss[i][j]);
        }
        result
    };

    for j in 1..m {
        if !is_sorted(&col(j)) {
            return None;
        }
    }

    Some(ii)
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let cases_num: u16 = scanner.next();

    for _ in 1..=cases_num {
        let n: usize = scanner.next();
        let m: usize = scanner.next();

        let mut xss: Vec<Vec<u16>> = vec![vec![0; m]; n];
        for row in xss.iter_mut() {
            for x in row.iter_mut() {
                *x = scanner.next();
            }
        }

        if let Some(ii) = solve(xss) {
            let result = ii
                .iter()
                .map(|i| (i + 1).to_string())
                .collect::<Vec<_>>()
                .join(" ");
            writeln!(writer, "{}", result).unwrap();
        } else {
            writeln!(writer, "-1").unwrap();
        }
    }

    writer.flush().unwrap();
}
