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
        (i0 + 1 - k..=i0).rev().map(Self::ShiftLeftA).collect()
    }

    fn k_right_a_shifts(i0: usize, k: usize) -> Vec<Self> {
        (i0..i0 + k).map(Self::ShiftRightA).collect()
    }

    fn k_left_b_shifts(i0: usize, k: usize) -> Vec<Self> {
        assert!(i0 >= k);
        (i0 + 1 - k..=i0).rev().map(Self::ShiftLeftB).collect()
    }

    fn k_right_b_shifts(i0: usize, k: usize) -> Vec<Self> {
        (i0..i0 + k).map(Self::ShiftRightB).collect()
    }
}

fn buble(row: usize, xs: &mut Vec<usize>, isource: usize, itarget: usize) -> Vec<Op> {
    let x0 = xs[isource];

    if itarget < isource {
        xs.remove(isource);
        xs.insert(itarget, x0);
        if row == 1 {
            Op::k_left_b_shifts(isource, isource - itarget)
        } else {
            assert_eq!(row, 0);
            Op::k_left_a_shifts(isource, isource - itarget)
        }
    } else if itarget > isource {
        xs.insert(itarget + 1, x0);
        xs.remove(isource);

        if row == 1 {
            Op::k_right_b_shifts(isource, itarget - isource)
        } else {
            assert_eq!(row, 0);
            Op::k_right_a_shifts(isource, itarget - isource)
        }
    } else {
        assert_eq!(itarget, isource);
        vec![]
    }
}

fn sorting_program(mut ab: Vec<Vec<usize>>) -> Vec<Op> {
    let n = ab[0].len();
    let mut result = vec![];

    for i in 0..n {
        if ab[0][i] > ab[1][i] {
            (ab[0][i], ab[1][i]) = (ab[1][i], ab[0][i]);
            result.push(Op::Swap(i));
        }
    }

    for x0 in 1..=n {
        let i = x0 - 1;

        if let Some(j) = ab[1].iter().position(|x| *x == x0) {
            result.extend(buble(1, &mut ab[1], j, i));

            result.push(Op::Swap(i));
            (ab[0][i], ab[1][i]) = (ab[1][i], ab[0][i]);
        } else {
            let j: usize = ab[0].iter().position(|x| *x == x0).unwrap();
            result.extend(buble(0, &mut ab[0], j, i));
        }
    }

    for x0 in n + 1..=2 * n {
        let i = x0 - n - 1;
        let j: usize = ab[1].iter().position(|x| *x == x0).unwrap();

        if i <= j {
            result.extend(buble(1, &mut ab[1], j, i));
        } else {
            assert!(j < i);
            result.extend(buble(0, &mut ab[0], j, i));
        }
    }

    assert!(ab[0].is_sorted());
    assert!(ab[1].is_sorted());
    assert!(ab[0].iter().zip(ab[1].iter()).all(|(x, y)| x < y));
    assert!(result.len() <= 1709);

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

        let prog = sorting_program(vec![a, b]);
        writeln!(writer, "{}", prog.len()).unwrap();

        for op in prog {
            writeln!(writer, "{}", op.represent()).unwrap();
        }
    }

    writer.flush().unwrap();
}
