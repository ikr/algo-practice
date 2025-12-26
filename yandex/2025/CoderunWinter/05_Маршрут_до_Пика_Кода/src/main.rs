use std::io::{stdin, stdout, BufWriter, Write};

#[derive(Clone, Copy, Debug)]
struct Crd([i32; 3]);

impl Crd {
    fn effort_to(self, o: Crd) -> u32 {
        self.0
            .iter()
            .zip(o.0)
            .map(|(a, b)| a.abs_diff(b))
            .min()
            .unwrap()
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
            let xyz: [i32; 3] = self.next_n(3).try_into().unwrap();
            result.push(Crd(xyz));
        }
        result
    }
}

fn min_total_effort(ps: Vec<Crd>) -> u64 {
    eprintln!("{:?}", ps);
    todo!()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let n: usize = scanner.next();
    let xs: Vec<Crd> = scanner.next_n_crds(n);

    let result = min_total_effort(xs);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
