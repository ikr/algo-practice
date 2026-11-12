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

fn solve(xs: Vec<usize>) -> usize {
    let n = xs.len();
    let front: Vec<usize> = xs[..n / 2].to_vec();
    let back: Vec<usize> = xs[n.div_ceil(2)..].iter().rev().copied().collect();
    assert_eq!(front.len(), back.len());

    let mut seq: Vec<usize> = (0..n / 2).into_iter().collect();
    seq.sort_by_key(|&i| front[i].max(back[i]));
    seq.reverse();

    let mut levels: Vec<usize> = (0..26).into_iter().collect();
    let mut result = 0;

    for i in seq {
        let (a, b) = (front[i].min(back[i]), front[i].max(back[i]));
        result += levels[b] - levels[a];

        for j in a + 1..=b {
            levels[j] = levels[a];
        }
    }

    result
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let cases_num: u16 = scanner.next();

    for _ in 1..=cases_num {
        let n: usize = scanner.next();
        let xs: String = scanner.next();
        assert_eq!(xs.len(), n);

        let result = solve(xs.bytes().map(|x| (x - b'a') as usize).collect());
        writeln!(writer, "{result}").unwrap();
    }

    writer.flush().unwrap();
}
