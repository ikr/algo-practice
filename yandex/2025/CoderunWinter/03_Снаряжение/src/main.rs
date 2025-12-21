use std::io::{stdin, stdout, BufWriter, Write};

const M: i64 = 1_000_000_007;

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

    fn next_n<T: std::str::FromStr>(&mut self, n: usize) -> Vec<T> {
        let mut result: Vec<T> = Vec::with_capacity(n);
        for _ in 0..n {
            result.push(self.next());
        }
        result
    }
}

fn prefix_sums<T: Copy + std::ops::Add<Output = T> + Default>(xs: &[T]) -> Vec<T> {
    xs.iter()
        .scan(T::default(), |state, x| {
            *state = *state + *x;
            Some(*state)
        })
        .collect()
}

fn rightmost_leveling_index(m: i64, xs: &[i64]) -> usize {
    let ss: Vec<i64> = prefix_sums(xs);
    let indexed: Vec<(usize, i64)> = ss.into_iter().enumerate().collect();
    indexed.partition_point(|&(i, x)| {
        if i == 0 {
            true
        } else {
            x - (i as i64 + 1) * xs[i] <= m
        }
    }) - 1
}

fn flaws_sum(mut m: i64, mut xs: Vec<i64>) -> i64 {
    let li = rightmost_leveling_index(m, &xs);
    if li == 0 {
        xs[li] -= m;
    } else {
        let level = xs[li];

        for x in xs.iter_mut().take(li + 1) {
            m -= *x - level;
            *x = level;
        }

        for i in (0..=li).rev() {
            if m == 0 {
                break;
            }
            xs[i] -= 1;
            m -= 1;
        }
    }

    xs.into_iter()
        .map(|x| {
            assert!(x >= 0);
            x.pow(2)
        })
        .fold(0, |acc, x| (acc + x) % M)
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);
    let mut scanner = Scanner::default();

    let m: i64 = scanner.next();
    let n: usize = scanner.next();
    let mut xs: Vec<i64> = scanner.next_n(n);
    xs.sort_by(|a, b| b.cmp(a));

    let result = flaws_sum(m, xs);
    writeln!(writer, "{result}").unwrap();

    writer.flush().unwrap();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_rightmost_leveling_index() {
        for (m, xs, expected) in [
            (5, vec![3, 2, 1], 2),
            (3, vec![5, 4, 3, 2], 2),
            (1, vec![1], 0),
            (1, vec![2, 2, 2, 2, 2, 2], 5),
            (1, vec![2, 1, 1, 1, 1, 1, 0], 5),
            (4, vec![5], 0),
        ] {
            assert_eq!(
                rightmost_leveling_index(m, &xs),
                expected,
                "Failing on {m}, {:?}",
                xs
            );
        }
    }
}
