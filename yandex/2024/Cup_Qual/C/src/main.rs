use std::io::{self, stdin, BufWriter, Write};

#[derive(Default)]
struct Scanner {
    buffer: Vec<String>,
}

impl Scanner {
    fn next_string(&mut self) -> String {
        loop {
            if let Some(token) = self.buffer.pop() {
                return token;
            }
            let mut input = String::new();
            stdin().read_line(&mut input).expect("Failed read");
            self.buffer = input.split_whitespace().rev().map(String::from).collect();
        }
    }
}

fn solve(bs: &[u8]) -> i32 {
    let n = bs.len();
    todo!();
}

fn span_when_all_definied(xs: &[u8]) -> i32 {
    let (lo, hi, _) = xs
        .iter()
        .fold((0i32, 0i32, 0i32), |(lo, hi, cur), x| match x {
            b'L' => (lo.min(cur - 1), hi, cur - 1),
            b'R' => (lo, hi.max(cur + 1), cur + 1),
            _ => panic!("Expecting only L-s and R-s; got {:?}", xs),
        });
    (lo - hi).abs()
}

fn bruteforce(xs: &[u8]) -> i32 {
    let q_indices = xs
        .iter()
        .enumerate()
        .filter(|(_, x)| **x == b'?')
        .map(|(i, _)| i)
        .collect::<Vec<_>>();
    let m = q_indices.len();
    assert!(m <= 20, "Brute-force is unfeasible with {} ?-s", m);

    let mut ys: Vec<u8> = xs.iter().cloned().collect();
    let mut result = 0;
    for bits in 0..(1 << m) {
        for i in 0..m {
            ys[q_indices[i]] = if (bits & (1 << i)) != 0 { b'L' } else { b'R' }
        }
        result = result.max(span_when_all_definied(&ys));
    }
    result
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let s: String = scanner.next_string();
    let bs: Vec<u8> = s.bytes().collect();
    let result = solve(&bs);
    writeln!(writer, "{}", result).unwrap();

    writer.flush().unwrap();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn span_when_all_defined_works() {
        assert_eq!(span_when_all_definied(b""), 0);
        assert_eq!(span_when_all_definied(b"RLRLRL"), 1);
        assert_eq!(span_when_all_definied(b"LLLL"), 4);
        assert_eq!(span_when_all_definied(b"LLLRRRRRR"), 6);
    }
}
