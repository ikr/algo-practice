use std::io::{stdin, stdout, BufWriter, Write};

#[derive(Clone, Copy)]
struct Crd(i32, i32);

impl Crd {
    fn manhattan(self) -> i32 {
        self.0.abs() + self.1.abs()
    }
}

enum Dir {
    N,
    E,
    S,
    W,
}

impl Dir {
    fn decode(b: u8) -> Self {
        match b {
            b'N' => Self::N,
            b'E' => Self::E,
            b'S' => Self::S,
            b'W' => Self::W,
            _ => unreachable!(),
        }
    }
}

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

    fn next_n_crds(&mut self, n: usize) -> Vec<Crd> {
        let mut result: Vec<Crd> = Vec::with_capacity(n);
        for _ in 0..n {
            let [x, y] = self.next_n(2).try_into().unwrap();
            result.push(Crd(x, y));
        }
        result
    }
}

fn sorted_xs_and_ys(ps: Vec<Crd>) -> (Vec<i32>, Vec<i32>) {
    let mut xs: Vec<i32> = ps.iter().map(|p| p.0).collect();
    xs.sort();

    let mut ys: Vec<i32> = ps.into_iter().map(|p| p.1).collect();
    ys.sort();

    (xs, ys)
}

fn step_right_delta(xs: &[i32], x0: i32) -> i64 {
    let n: i64 = xs.len() as i64;
    let lhs: i64 = xs.partition_point(|&x| x <= x0) as i64;
    let rhs: i64 = n - lhs;
    lhs - rhs
}

fn step_left_delta(xs: &[i32], x0: i32) -> i64 {
    let n: i64 = xs.len() as i64;
    let lhs: i64 = xs.partition_point(|&x| x < x0) as i64;
    let rhs: i64 = n - lhs;
    -lhs + rhs
}

fn distances_by_move(ps: Vec<Crd>, ds: Vec<Dir>) -> Vec<i64> {
    let mut cur: i64 = ps.iter().map(|p| p.manhattan() as i64).sum();
    let (xs, ys) = sorted_xs_and_ys(ps);
    let (mut x0, mut y0) = (0, 0);
    let mut result = vec![];

    for dir in ds {
        match dir {
            Dir::N => {
                let dy = step_right_delta(&ys, y0);
                y0 += 1;
                cur += dy;
            }
            Dir::E => {
                let dx = step_right_delta(&xs, x0);
                x0 += 1;
                cur += dx;
            }
            Dir::S => {
                let dy = step_left_delta(&ys, y0);
                y0 -= 1;
                cur += dy;
            }
            Dir::W => {
                let dx = step_left_delta(&xs, x0);
                x0 -= 1;
                cur += dx;
            }
        }

        result.push(cur);
    }

    result
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let n: usize = scanner.next();
    let m: usize = scanner.next();
    let ps: Vec<Crd> = scanner.next_n_crds(n);
    let s: String = scanner.next();
    let ds: Vec<Dir> = s.bytes().map(Dir::decode).collect();
    assert_eq!(ds.len(), m);

    for a in distances_by_move(ps, ds) {
        writeln!(writer, "{a}").unwrap();
    }
    writer.flush().unwrap();
}
