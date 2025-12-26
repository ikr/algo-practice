use std::io::{stdin, stdout, BufWriter, Write};

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i32, i32);

impl Crd {
    fn manhattan(self) -> i32 {
        self.0.abs() + self.1.abs()
    }
}

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

#[derive(Clone, Copy, Debug)]
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

    fn delta(&self) -> Crd {
        match self {
            Dir::N => Crd(-1, 0),
            Dir::E => Crd(0, 1),
            Dir::S => Crd(1, 0),
            Dir::W => Crd(0, -1),
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

fn distances_by_move(ps: Vec<Crd>, ds: Vec<Dir>) -> Vec<u64> {
    eprintln!("{:?} {:?}", ps, ds);
    todo!()
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
