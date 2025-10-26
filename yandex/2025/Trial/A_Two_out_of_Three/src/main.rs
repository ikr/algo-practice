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
}

fn nth_number_divisible_by_two_out_of_three(abc: [usize; 3], n: usize) -> Option<usize> {
    None
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
    let n: usize = scanner.next();

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
    fn test_nth_number_divisible_by_two_out_of_three() {
        assert_eq!(
            brute_nth_number_divisible_by_two_out_of_three([2, 3, 5], 10),
            Some(42)
        );
        assert_eq!(
            brute_nth_number_divisible_by_two_out_of_three([5, 6, 7], 1000000),
            Some(13999986)
        );

        let samples = vec![([1, 1, 1], 1023), ([1, 1, 2], 1023), ([7, 14, 2], 1023)];
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
