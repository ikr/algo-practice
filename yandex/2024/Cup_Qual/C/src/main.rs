use std::{
    collections::HashSet,
    io::{self, stdin, BufWriter, Write},
};

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

    let mut lo: i32 = 0;
    let mut hi: i32 = 0;
    let mut cur: i32 = 0;

    let mut ls: HashSet<usize> = HashSet::new();

    for (i, x) in bs.iter().enumerate() {
        match x {
            b'L' => cur += 1,
            b'R' => cur -= 1,
            _ => {
                if i != 0 && (bs[i - 1] == b'L' || ls.contains(&(i - 1))) {
                    cur -= 1;
                    ls.insert(i);
                } else {
                    cur += 1;
                }
            }
        }

        lo = lo.min(cur);
        hi = hi.max(cur);
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
