use std::{
    collections::HashSet,
    io::{stdin, stdout, BufWriter, Write},
};

type Fact = Vec<(u8, u8)>;
type Fexp = Vec<u8>;

const PRIMES: [u8; 15] = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47];

fn value_of(f: Fact) -> Option<u64> {
    f.into_iter().try_fold(1u64, |acc, (p, e)| {
        (p as u64)
            .checked_pow(e as u32)
            .and_then(|a| acc.checked_mul(a))
    })
}

fn concat<T>(mut xs: Vec<T>, ys: Vec<T>) -> Vec<T> {
    xs.extend(ys);
    xs
}

fn fact_of_fexp(fe: Fexp) -> Fact {
    assert_eq!(fe.len(), PRIMES.len());
    PRIMES.iter().copied().zip(fe).collect()
}

fn divs_count(fe: Fexp) -> u64 {
    fe.into_iter().map(|a| (a + 1) as u64).product()
}

fn gen_fexps(acc: &mut HashSet<Fexp>, u: Fexp) {
    let n = u.len();

    let ij: Vec<(usize, usize)> = u
        .iter()
        .enumerate()
        .skip(1)
        .filter_map(|(i, &x)| if x < u[i - 1] { Some(i - 1) } else { None })
        .filter_map(|i| (i + 1..n).find(|&j| u[i] > u[j] + 1).map(|j| (i, j)))
        .collect();

    for (i, j) in ij {
        let mut v = u.clone();
        v[i] -= 1;
        v[j] += 1;

        if !acc.contains(&v) && value_of(fact_of_fexp(v.clone())).is_some() {
            acc.insert(v.clone());
            gen_fexps(acc, v);
        }
    }
}

fn all_artefacts() -> Vec<u64> {
    let mut fexps_set: HashSet<Fexp> = HashSet::new();
    for k in 0..61 {
        let u0 = concat(vec![k], vec![0; PRIMES.len() - 1]);
        fexps_set.insert(u0.clone());
        gen_fexps(&mut fexps_set, u0);
    }

    let mut fexps: Vec<Fexp> = fexps_set.into_iter().collect();
    fexps.sort_by_key(|fexp| value_of(fact_of_fexp(fexp.clone())).unwrap());

    let mut hi: u64 = 0;
    let mut result = vec![];

    for fe in fexps {
        if divs_count(fe.clone()) > hi {
            hi = divs_count(fe.clone());
            result.push(value_of(fact_of_fexp(fe)).unwrap());
        }
    }

    result
}

fn artefacts_count(aa: &[u64], a: u64, b: u64) -> usize {
    let i = aa.partition_point(|&x| x < a);
    let j = aa.partition_point(|&x| x <= b);
    j - i
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
    let aa = all_artefacts();

    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);
    let mut scanner = Scanner::default();

    let q: u16 = scanner.next();
    for _ in 0..q {
        let a: u64 = scanner.next();
        let b: u64 = scanner.next();
        let result = artefacts_count(&aa, a, b);
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
