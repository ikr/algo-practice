use std::io::{BufRead, stdin};

fn eni(n: u64, exp: u64, m: u64) -> u64 {
    let rems: Vec<u64> = (0..exp)
        .scan(1u64, |score, _| {
            *score = *score * n;
            *score = *score % m;
            Some(*score)
        })
        .collect();

    rems.into_iter()
        .rev()
        .take(5)
        .map(|r| r.to_string())
        .collect::<Vec<_>>()
        .join("")
        .parse()
        .unwrap()
}

struct Args {
    abc: [u64; 3],
    xyz: [u64; 3],
    m: u64,
}

impl Args {
    fn decode_one(s: &str) -> u64 {
        let parts = s.split('=').collect::<Vec<_>>();
        parts[1].parse().unwrap()
    }

    fn decode(s: &str) -> Self {
        let parts = s.split_whitespace().collect::<Vec<_>>();
        let abc: Vec<u64> = parts[..3].iter().map(|s| Self::decode_one(*s)).collect();
        let xyz: Vec<u64> = parts[3..6].iter().map(|s| Self::decode_one(*s)).collect();
        let m: u64 = Self::decode_one(parts[6]);

        Self {
            abc: abc.try_into().unwrap(),
            xyz: xyz.try_into().unwrap(),
            m,
        }
    }

    fn three_sum(&self) -> u64 {
        self.abc
            .into_iter()
            .zip(self.xyz.into_iter())
            .map(|(p, q)| eni(p, q, self.m))
            .sum()
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let args: Vec<Args> = lines.into_iter().map(|s| Args::decode(&s)).collect();
    let xs: Vec<u64> = args.into_iter().map(|a| a.three_sum()).collect();
    let result = xs.into_iter().max().unwrap();
    println!("{}", result);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_eni() {
        assert_eq!(eni(2, 7, 5), 34213);
        assert_eq!(eni(3, 8, 16), 111931);
    }
}
