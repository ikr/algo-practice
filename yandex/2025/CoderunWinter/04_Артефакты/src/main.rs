use std::{
    io::{stdin, stdout, BufWriter, Write},
    iter::successors,
};

type Fact = Vec<(u64, u32)>;

const PRIMES: [u64; 15] = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47];

fn base_fact() -> Fact {
    PRIMES.into_iter().map(|p| (p, 0)).collect()
}

fn value_of(f: Fact) -> Option<u64> {
    f.into_iter().try_fold(1u64, |acc, (p, e)| {
        if let Some(a) = p.checked_pow(e) {
            if let Some(b) = acc.checked_mul(a) {
                Some(b)
            } else {
                None
            }
        } else {
            None
        }
    })
}

fn bumped_fact(mut f: Fact, i: usize) -> Fact {
    f[i].1 += 1;
    f
}

fn next_fact_bump_index(f: Fact) -> Option<usize> {
    let n = f.len();

    let ii: Vec<usize> = (0..n)
        .filter(|&i| {
            (i == 0 || f[i - 1].1 > f[i].1) && value_of(bumped_fact(f.clone(), i)).is_some()
        })
        .collect();

    eprintln!("ii:{:?} for f:{:?}", ii, f);

    ii.into_iter()
        .min_by_key(|&i| value_of(bumped_fact(f.clone(), i)).unwrap())
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

fn all_artefacts() -> Vec<u64> {
    successors(Some(base_fact()), |f| {
        next_fact_bump_index(f.clone()).map(|i| bumped_fact(f.clone(), i))
    })
    .map(|f| value_of(f).unwrap())
    .collect()
}

fn artefacts_count(a: u64, b: u64) -> usize {
    todo!()
}

fn main() {
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
