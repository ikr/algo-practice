use std::io::{BufWriter, Write, stdin, stdout};

enum Player {
    A,
    B,
}

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

fn winner_is(aa: Vec<usize>, bb: Vec<usize>) -> Player {
    let n = aa.len() + bb.len();
    if n == 2 {
        return if aa[0] == 0 { Player::A } else { Player::B };
    }

    let ahi = *aa.last().unwrap();
    let bhi = *bb.last().unwrap();

    if aa[0] == 0 && ahi == n - 1 {
        return Player::A;
    }
    if bb[0] == 0 && bhi == n - 1 {
        return Player::B;
    }
    if aa.len() == 1 {
        return Player::B;
    }
    if bb.len() == 1 {
        return Player::A;
    }
    if [n - 2, n - 1].iter().all(|j| aa.contains(j)) {
        return Player::A;
    }
    Player::B
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let cases_num: u16 = scanner.next();

    for _ in 1..=cases_num {
        let n: usize = scanner.next();
        let s: String = scanner.next();
        assert_eq!(s.len(), n);
        let mut aa: Vec<usize> = vec![];
        let mut bb: Vec<usize> = vec![];

        for (i, &x) in s.into_bytes().iter().enumerate() {
            if x == b'A' {
                aa.push(i);
            } else {
                assert_eq!(x, b'B');
                bb.push(i);
            }
        }

        let result = match winner_is(aa, bb) {
            Player::A => "Alice",
            Player::B => "Bob",
        };
        writeln!(writer, "{}", result).unwrap();
    }

    writer.flush().unwrap();
}
