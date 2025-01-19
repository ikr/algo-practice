use std::io::{self, stdin, BufWriter, Write};

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

fn fibonacciness(xs: &[i16]) -> usize {
    xs.windows(3).filter(|a| a[0] + a[1] == a[2]).count()
}

fn infix_with(xs: [i16; 4], x0: i16) -> [i16; 5] {
    [xs[0], xs[1], x0, xs[2], xs[3]]
}

fn solve(xs: [i16; 4]) -> usize {
    [
        infix_with(xs, xs[0] + xs[1]),
        infix_with(xs, xs[2] - xs[1]),
        infix_with(xs, xs[3] - xs[2]),
    ]
    .into_iter()
    .map(|ys| fibonacciness(&ys))
    .max()
    .unwrap()
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let cases_num: i16 = scanner.next();

    for _ in 1..=cases_num {
        let mut xs: [i16; 4] = [0, 0, 0, 0];
        for x in xs.iter_mut() {
            *x = scanner.next();
        }

        let result = solve(xs);
        writeln!(writer, "{}", result).unwrap();
    }

    writer.flush().unwrap();
}
