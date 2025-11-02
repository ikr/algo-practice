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
}

fn max_common_area(aa: Vec<Vec<u32>>, bb: Vec<Vec<u32>>) -> usize {
    todo!()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let cases_num: u16 = scanner.next();

    for _ in 1..=cases_num {
        let h: usize = scanner.next();
        let w: usize = scanner.next();

        let mut read_grid = || -> Vec<Vec<u32>> {
            let mut grid: Vec<Vec<u32>> = vec![];
            for _ in 0..h {
                let s: String = scanner.next();
                let row = s.bytes().map(|b| (b - b'0') as u32).collect::<Vec<_>>();
                assert_eq!(row.len(), w);
                grid.push(row)
            }
            grid
        };

        let aa = read_grid();
        let bb = read_grid();
        let result = max_common_area(aa, bb);
        writeln!(writer, "{result}").unwrap();
    }

    writer.flush().unwrap();
}
