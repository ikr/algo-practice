use std::io::Read;

fn digits_reversed(mut x: u64) -> Vec<u64> {
    if x == 0 {
        return vec![0];
    }

    let mut ans = vec![];
    while x != 0 {
        ans.push(x % 10);
        x /= 10;
    }
    ans
}

fn digits(x: u64) -> Vec<u64> {
    let mut result = digits_reversed(x);
    result.reverse();
    result
}

fn number(ds: Vec<u64>) -> u64 {
    if ds.is_empty() {
        0
    } else {
        let mut ans = 0;
        let mut mul = 1;

        for d in ds.into_iter().rev() {
            ans += d * mul;
            mul *= 10;
        }

        ans
    }
}

fn repeat_k_times(pattern: &[u64], k: usize) -> Vec<u64> {
    let mut result = vec![];
    for _ in 0..k {
        result.extend(pattern);
    }
    result
}

fn is_invalid_id(x: u64) -> bool {
    let ds = digits(x);
    let n = ds.len();

    (1..=n / 2 + 1).any(|p| {
        if n % p == 0 {
            let q = n / p;
            q == 2 && number(repeat_k_times(&ds[0..p], q)) == x
        } else {
            false
        }
    })
}

fn decode_range(s: &str) -> (u64, u64) {
    let parts = s.split('-').collect::<Vec<_>>();
    (parts[0].parse().unwrap(), parts[1].parse().unwrap())
}

fn main() {
    let mut buf: String = String::new();
    std::io::stdin().read_to_string(&mut buf).unwrap();

    let range_sources = buf.trim().split(',').collect::<Vec<_>>();
    let ranges: Vec<(u64, u64)> = range_sources.into_iter().map(decode_range).collect();

    let xs: Vec<u64> = ranges
        .into_iter()
        .flat_map(|(a, b)| (a..=b).collect::<Vec<_>>())
        .collect();

    let invalid: Vec<u64> = xs.into_iter().filter(|&x| is_invalid_id(x)).collect();
    eprintln!("{:?}", invalid);
    let result: u64 = invalid.into_iter().sum();
    println!("{result}");
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_is_invalid_id() {
        assert!(is_invalid_id(11));
        assert!(!is_invalid_id(12));
        assert!(!is_invalid_id(113112));
        assert!(is_invalid_id(113113));
    }
}
