use std::io::{BufWriter, Write, stdin, stdout};

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

fn streak_lengths(xs: Vec<i64>) -> Vec<usize> {
    let n = xs.len();
    let mut i0: usize = 0;
    let mut result = vec![];

    while i0 < n {
        let mb_i = xs[i0..]
            .windows(2)
            .map(|ab| (ab[0], ab[1]))
            .position(|(a, b)| a + 1 != b);

        if let Some(i) = mb_i {
            result.push(i + 1);
            i0 += i + 1;
        } else {
            result.push(n - i0);
            i0 = n;
        }
    }

    result
}

fn max_post_adjustment_mex(mut xs: Vec<i64>) -> usize {
    xs.sort();
    xs.dedup();
    let ls = streak_lengths(xs);
    ls.into_iter().max().unwrap()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let cases_num: u16 = scanner.next();

    for _ in 1..=cases_num {
        let n: usize = scanner.next();
        let xs: Vec<i64> = scanner.next_n(n);

        let result = max_post_adjustment_mex(xs);
        writeln!(writer, "{result}").unwrap();
    }

    writer.flush().unwrap();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_streak_lengths() {
        for (arg, res) in [
            (vec![1], vec![1]),
            (vec![1, 2, 3], vec![3]),
            (vec![1, 2, 3, 1], vec![3, 1]),
            (vec![1, 2, 3, 1, 2, 3], vec![3, 3]),
            (vec![-1, 1, 2, 3, 5, 6], vec![1, 3, 2]),
        ] {
            assert_eq!(streak_lengths(arg.clone()), res, "Failing on {:?}", arg);
        }
    }
}
