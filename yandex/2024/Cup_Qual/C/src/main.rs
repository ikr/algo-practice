use std::io::{self, stdin, BufWriter, Write};

#[derive(Default)]
struct Scanner {
    buffer: Vec<String>,
}

impl Scanner {
    fn next_string(&mut self) -> String {
        loop {
            if let Some(token) = self.buffer.pop() {
                return token;
            }
            let mut input = String::new();
            stdin().read_line(&mut input).expect("Failed read");
            self.buffer = input.split_whitespace().rev().map(String::from).collect();
        }
    }
}

fn solve(xs: String) -> i32 {
    let bs = xs.bytes().collect::<Vec<_>>();
    let n = bs.len();
    let mut dpl: Vec<(i32, i32)> = vec![(0, 0); n];
    let mut dpr: Vec<(i32, i32)> = vec![(0, 0); n];

    dpl[0] = match bs[0] {
        b'L' => (-1, -1),
        b'R' => (1, 1),
        _ => (-1, -1),
    };

    dpr[0] = match bs[0] {
        b'L' => (-1, -1),
        b'R' => (1, 1),
        _ => (1, 1),
    };

    for i in 1..n {
        let (a, b) = dpl[i - 1];
        let (c, d) = dpr[i - 1];

        let lo = a.min(c);
        let hi = b.max(d);

        dpl[i] = match bs[i] {
            b'L' => (lo - 1, hi - 1),
            b'R' => (lo + 1, hi + 1),
            _ => (lo - 1, hi - 1),
        };

        dpr[i] = match bs[i] {
            b'L' => (lo - 1, hi - 1),
            b'R' => (lo + 1, hi + 1),
            _ => (lo + 1, hi + 1),
        };
    }

    let mut lo: i32 = 0;
    let mut hi: i32 = 0;

    for (a, b) in dpl {
        lo = lo.min(a);
        hi = hi.max(b);
    }

    for (a, b) in dpr {
        lo = lo.min(a);
        hi = hi.max(b);
    }

    (lo - hi).abs()
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let s: String = scanner.next_string();
    let result = solve(s);
    writeln!(writer, "{}", result).unwrap();

    writer.flush().unwrap();
}
