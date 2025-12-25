use std::io::{stdin, stdout, BufWriter, Write};

type Fact = Vec<(u8, u8)>;
type Fexp = Vec<u8>;

const PRIMES: [u8; 15] = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47];

fn base_fact() -> Fact {
    PRIMES.iter().map(|&p| (p, 0)).collect()
}

fn value_of(f: Fact) -> Option<u64> {
    f.into_iter().try_fold(1u64, |acc, (p, e)| {
        (p as u64)
            .checked_pow(e as u32)
            .and_then(|a| acc.checked_mul(a))
    })
}

fn all_artefacts() -> Vec<u64> {
    todo!()
}

fn artefacts_count(a: u64, b: u64) -> usize {
    todo!()
}

fn concat<T>(mut xs: Vec<T>, ys: Vec<T>) -> Vec<T> {
    xs.extend(ys);
    xs
}

fn gen_fexps(k: u8, offset: usize) -> Vec<Fexp> {
    if k == 0 || offset == PRIMES.len() {
        return vec![];
    }

    let mut result = vec![vec![k]];

    for i in (k / 2..k).rev() {
        for tail in gen_fexps(k - i, offset + 1) {
            result.push(concat(vec![i], tail));
        }
    }

    result
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

fn main() {
    eprintln!("{:?}", gen_fexps(4, 0));

    let aa = all_artefacts();
    eprintln!("{:?}", aa);

    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);
    let mut scanner = Scanner::default();

    let q: u16 = scanner.next();
    for _ in 0..q {
        let a: u64 = scanner.next();
        let b: u64 = scanner.next();
        let result = artefacts_count(a, b);
        writeln!(writer, "{result}").unwrap();
    }

    writer.flush().unwrap();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_value_of() {
        for (f, exp) in [
            (vec![(2, 10)], Some(1024)),
            (vec![(2, 80)], None),
            (vec![(2, 1), (3, 1)], Some(6)),
        ] {
            assert_eq!(value_of(f), exp);
        }
    }
}
