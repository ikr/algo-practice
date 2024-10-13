use std::{
    cmp::Reverse,
    collections::BinaryHeap,
    io::{self, stdin, BufWriter, Write},
};

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

fn solve(xs: &[i32]) -> i32 {
    let mut heap = xs.iter().map(|x| Reverse(*x)).collect::<BinaryHeap<_>>();

    while let Some(Reverse(x)) = heap.pop() {
        if let Some(Reverse(y)) = heap.pop() {
            let z: i32 = (x + y) / 2;
            heap.push(Reverse(z));
        } else {
            return x;
        }
    }

    panic!("Empty heap")
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let cases_num: u16 = scanner.next();

    for _ in 1..=cases_num {
        let n: usize = scanner.next();
        let mut xs: Vec<i32> = vec![0; n];
        for x in xs.iter_mut() {
            *x = scanner.next();
        }

        let result = solve(&xs);
        writeln!(writer, "{}", result).unwrap();
    }

    writer.flush().unwrap();
}
