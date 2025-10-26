use std::io::{BufWriter, Write, stdin, stdout};

const CAP: usize = 1_000_000 * 1_000_000 * 1_000_000;

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

// Stein's algo from https://gist.github.com/cmpute/0a09749f76303b24b7961362bee8d988
fn gcd(mut m: usize, mut n: usize) -> usize {
    if m == 0 || n == 0 {
        return m | n;
    }

    // find common factors of 2
    let shift = (m | n).trailing_zeros();

    // divide n and m by 2 until odd
    // m inside loop
    n >>= n.trailing_zeros();

    while m != 0 {
        m >>= m.trailing_zeros();
        if n > m {
            std::mem::swap(&mut n, &mut m)
        }
        m -= n;
    }

    n << shift
}

fn lcm(x: usize, y: usize) -> usize {
    (x * y) / gcd(x, y)
}

fn distinct(abc: [usize; 3]) -> Vec<usize> {
    assert!(abc.is_sorted());
    let mut xs = abc.to_vec();
    xs.dedup();
    xs
}

fn nth_number_divisible_by_either(n: usize, ab: [usize; 2]) -> Option<usize> {
    let [a, b] = ab;
    assert_ne!(a, b);
    let mut lo: usize = 0;
    let mut hi: usize = CAP;

    while lo + 1 < hi {
        let mid = lo + (hi - lo) / 2;
        let cur = (mid / a + mid / b) - 2 * mid / lcm(a, b);

        if cur > n {
            hi = mid;
        } else {
            lo = mid;
        }
    }

    if lo > CAP { None } else { Some(lo) }
}

fn nth_number_divisible_by_two_out_of_three(abc: [usize; 3], n: usize) -> Option<usize> {
    if distinct(abc).len() == 1 {
        return None;
    }

    let [a, b, c] = abc;
    if a == b {
        return nth_number_divisible_by_either(n, [b, c]);
    } else if b == c {
        return nth_number_divisible_by_either(n, [a, b]);
    }

    let mut lo: usize = 0;
    let mut hi: usize = CAP;

    while lo + 1 < hi {
        let mid = lo + (hi - lo) / 2;
        let cur = (mid / lcm(a, b) + mid / lcm(b, c) + mid / lcm(a, c)) - 3 * lcm(lcm(a, b), c);

        if cur > n {
            hi = mid;
        } else {
            lo = mid;
        }
    }

    if lo > CAP { None } else { Some(lo) }
}

fn brute_nth_number_divisible_by_two_out_of_three(abc: [usize; 3], n: usize) -> Option<usize> {
    (1..14_000_000)
        .filter(|x| abc.iter().filter(|&q| x % q == 0).count() == 2)
        .nth(n - 1)
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);
    let mut scanner = Scanner::default();

    let mut abc = [0, 0, 0];
    for x in &mut abc {
        *x = scanner.next();
    }
    abc.sort();
    let mut n: usize = scanner.next();

    let result = nth_number_divisible_by_two_out_of_three(abc, n);
    if let Some(x) = result {
        writeln!(writer, "{x}").unwrap();
    } else {
        writeln!(writer, "-1").unwrap();
    }

    writer.flush().unwrap();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_gcd() {
        for (a, b, res) in vec![(1, 1, 1), (2, 3, 1), (2, 4, 2), (234_234, 2_398_473, 693)] {
            assert_eq!(gcd(a, b), res);
        }
    }

    #[test]
    fn test_nth_number_divisible_by_two_out_of_three() {
        assert_eq!(
            brute_nth_number_divisible_by_two_out_of_three([2, 3, 5], 10),
            Some(42)
        );
        assert_eq!(
            brute_nth_number_divisible_by_two_out_of_three([5, 6, 7], 1000000),
            Some(13999986)
        );

        let samples = vec![
            ([1, 1, 1], 1023),
            ([1, 1, 2], 1023),
            ([3, 3, 13], 200),
            ([2, 7, 14], 1023),
        ];
        for (abc, n) in samples {
            assert_eq!(
                nth_number_divisible_by_two_out_of_three(abc, n),
                brute_nth_number_divisible_by_two_out_of_three(abc, n),
                "on {:?} {n}",
                abc
            );
        }
    }
}
