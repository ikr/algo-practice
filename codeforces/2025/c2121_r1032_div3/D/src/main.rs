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

#[derive(Clone, Copy, Debug)]
enum Op {
    ShiftLeftA(usize),
    ShiftRightA(usize),
    ShiftLeftB(usize),
    ShiftRightB(usize),
    Swap(usize),
}

impl Op {
    fn represent(self) -> String {
        match self {
            Self::ShiftLeftA(i) => String::from("1 ") + &i.to_string(),
            Self::ShiftRightA(i) => String::from("1 ") + &(i + 1).to_string(),
            Self::ShiftLeftB(i) => String::from("2 ") + &i.to_string(),
            Self::ShiftRightB(i) => String::from("2 ") + &(i + 1).to_string(),
            Self::Swap(i) => String::from("3 ") + &(i + 1).to_string(),
        }
    }

    fn k_left_a_shifts(i0: usize, k: usize) -> Vec<Self> {
        assert!(i0 >= k);
        (i0 + 1 - k..=i0)
            .rev()
            .map(|i| Self::ShiftLeftA(i))
            .collect()
    }

    fn k_right_a_shifts(i0: usize, k: usize) -> Vec<Self> {
        (i0..i0 + k).map(|i| Self::ShiftRightA(i)).collect()
    }

    fn k_left_b_shifts(i0: usize, k: usize) -> Vec<Self> {
        assert!(i0 >= k);
        (i0 + 1 - k..=i0)
            .rev()
            .map(|i| Self::ShiftLeftB(i))
            .collect()
    }

    fn k_right_b_shifts(i0: usize, k: usize) -> Vec<Self> {
        (i0..i0 + k).map(|i| Self::ShiftRightB(i)).collect()
    }
}

fn sorting_program(mut a: Vec<usize>, mut b: Vec<usize>) -> Vec<Op> {
    let n = a.len();
    let mut result = vec![];

    for i in 0..n {
        if a[i] > b[i] {
            (a[i], b[i]) = (b[i], a[i]);
            result.push(Op::Swap(i));
        }
    }

    for x0 in 1..=n {
        let i = x0 - 1;

        if let Some(j) = b.iter().position(|x| *x == x0) {
            if i < j {
                result.extend(Op::k_left_b_shifts(j, j - i));
                b.remove(j);
                b.insert(i, x0);
            } else if i > j {
                result.extend(Op::k_right_b_shifts(j, i - j));
                b.insert(i + 1, x0);
                b.remove(j);
            }

            result.push(Op::Swap(i));
            (a[i], b[i]) = (b[i], a[i]);
        } else {
            let j: usize = a.iter().position(|x| *x == x0).unwrap();
            if i < j {
                result.extend(Op::k_left_a_shifts(j, j - i));
                a.remove(j);
                a.insert(i, x0);
            } else if i > j {
                result.extend(Op::k_right_a_shifts(j, i - j));
                a.insert(i + 1, x0);
                a.remove(j);
            }
        }
    }

    for x0 in n + 1..=2 * n {
        let i = x0 - n - 1;
        let j: usize = b.iter().position(|x| *x == x0).unwrap();

        if i <= j {
            result.extend(Op::k_left_b_shifts(j, j - i));
            b.remove(j);
            b.insert(i, x0);
        } else {
            assert!(j < i);
            result.extend(Op::k_right_b_shifts(j, i - j));
            b.remove(j);
            b.insert(i - 1, x0);
        }
    }

    assert!(result.len() <= 1709);
    assert_eq!(a, (1..=n).collect::<Vec<_>>());
    assert_eq!(b, (n + 1..=2 * n).collect::<Vec<_>>());

    result
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let cases_num: u16 = scanner.next();

    for _ in 1..=cases_num {
        let n: usize = scanner.next();
        let a: Vec<usize> = scanner.next_n(n);
        let b: Vec<usize> = scanner.next_n(n);

        let prog = sorting_program(a, b);
        writeln!(writer, "{}", prog.len()).unwrap();

        for op in prog {
            writeln!(writer, "{}", op.represent()).unwrap();
        }
    }

    writer.flush().unwrap();
}
