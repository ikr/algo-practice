use ac_library::ModInt as Mint;
use std::io::{BufRead, stdin};

fn eni(n: u64, exp: u64, m: u32) -> u64 {
    Mint::set_modulus(m);
    let nn = Mint::new(n);
    let result = nn.pow(exp + 1) * (Mint::new(1) - Mint::new(n)).inv();
    result.val() as u64
}

struct Args {
    abc: [u64; 3],
    xyz: [u64; 3],
    m: u32,
}

impl Args {
    fn decode_one(s: &str) -> u64 {
        let parts = s.split('=').collect::<Vec<_>>();
        parts[1].parse().unwrap()
    }

    fn decode(s: &str) -> Self {
        let parts = s.split_whitespace().collect::<Vec<_>>();
        let abc: Vec<u64> = parts[..3].iter().map(|s| Self::decode_one(s)).collect();
        let xyz: Vec<u64> = parts[3..6].iter().map(|s| Self::decode_one(s)).collect();
        let m: u32 = Self::decode_one(parts[6]) as u32;

        Self {
            abc: abc.try_into().unwrap(),
            xyz: xyz.try_into().unwrap(),
            m,
        }
    }

    // eni(A, X, M) + eni(B, Y, M) + eni(C, Z, M)
    fn three_sum(&self) -> u64 {
        self.abc
            .into_iter()
            .zip(self.xyz)
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
        assert_eq!(eni(2, 7, 5), 19);
        assert_eq!(eni(3, 8, 16), 48);
    }
}
