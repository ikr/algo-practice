use std::{
    collections::VecDeque,
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
}

enum Answer {
    Impossible,
    PlayerMoves(Vec<usize>, Vec<usize>),
}

fn score_model(n: usize, a: usize, b: usize) -> Answer {
    if a + b > n {
        Answer::Impossible
    } else {
        let ties = n - a - b;
        let mut aa: VecDeque<usize> = (ties + 1..=n).collect();
        let mut bb = aa.clone();
        let mut xs: Vec<usize> = (1..=ties).collect();
        let mut ys: Vec<usize> = (1..=ties).collect();

        for _ in 0..a {
            if let Some(a) = aa.pop_back() {
                if let Some(b) = bb.pop_front() {
                    xs.push(a);
                    ys.push(b);
                } else {
                    return Answer::Impossible;
                }
            } else {
                return Answer::Impossible;
            }
        }

        for _ in 0..b {
            if let Some(b) = bb.pop_back() {
                if let Some(a) = aa.pop_front() {
                    xs.push(a);
                    ys.push(b);
                } else {
                    return Answer::Impossible;
                }
            } else {
                return Answer::Impossible;
            }
        }

        Answer::PlayerMoves(xs, ys)
    }
}

fn vec_str(xs: Vec<usize>) -> String {
    xs.into_iter()
        .map(|x| x.to_string())
        .collect::<Vec<_>>()
        .join(" ")
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let cases_num: u16 = scanner.next();

    for _ in 1..=cases_num {
        let n: usize = scanner.next();
        let a: usize = scanner.next();
        let b: usize = scanner.next();

        match score_model(n, a, b) {
            Answer::Impossible => writeln!(writer, "NO").unwrap(),
            Answer::PlayerMoves(xs, ys) => {
                writeln!(writer, "YES").unwrap();
                writeln!(writer, "{}", vec_str(xs)).unwrap();
                writeln!(writer, "{}", vec_str(ys)).unwrap();
            }
        }
    }

    writer.flush().unwrap();
}
