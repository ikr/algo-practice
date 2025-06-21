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

fn locate(ab: &[Vec<usize>], x0: usize) -> (usize, usize) {
    for (i, row) in ab.iter().enumerate() {
        for (j, &x) in row.iter().enumerate() {
            if x == x0 {
                return (i, j);
            }
        }
    }
    unreachable!()
}

fn plan_a(n: usize) -> Vec<Vec<usize>> {
    vec![(1..=n).collect(), (n + 1..=2 * n).collect()]
}

fn plan_b(n: usize) -> Vec<Vec<usize>> {
    vec![
        (1..=2 * n).step_by(2).collect(),
        (2..=2 * n).step_by(2).collect(),
    ]
}

fn sorting_program_for_plan(mut ab: Vec<Vec<usize>>, plan: Vec<Vec<usize>>) -> Vec<Op> {
    let mut result = vec![];

    for (i1, row) in plan.into_iter().enumerate() {
        for (j1, x0) in row.into_iter().enumerate() {
            let (i0, j0) = locate(&ab, x0);

            result.extend(buble(i0, &mut ab[i0], j0, j1));
            if i0 != i1 {
                result.push(Op::Swap(j1));
                (ab[i0][j1], ab[i1][j1]) = (ab[i1][j1], ab[i0][j1]);
            }
        }
    }

    result
}

fn sorting_program(ab: Vec<Vec<usize>>) -> Vec<Op> {
    let n = ab[0].len();
    let o1 = sorting_program_for_plan(ab.clone(), plan_a(n));
    let o2 = sorting_program_for_plan(ab, plan_b(n));
    if o1.len() <= o2.len() { o1 } else { o2 }
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
