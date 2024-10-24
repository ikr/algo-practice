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

fn spell_casts_num(grid: &[Vec<i32>]) -> i32 {
    let n = grid.len();
    let mut result = 0;

    for co0 in 0..n {
        let mut co = co0;
        let mut ro: usize = 0;
        let mut lo = 0;

        while co < n && ro < n {
            lo = lo.min(grid[ro][co]);
            ro += 1;
            co += 1;
        }

        result += -lo;
    }

    for ro0 in 1..n {
        let mut ro = ro0;
        let mut co: usize = 0;
        let mut lo = 0;

        while ro < n && co < n {
            lo = lo.min(grid[ro][co]);
            ro += 1;
            co += 1;
        }

        result += -lo;
    }

    result
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let cases_num: u16 = scanner.next();

    for _ in 1..=cases_num {
        let n: usize = scanner.next();
        let mut grid: Vec<Vec<i32>> = vec![vec![0; n]; n];

        for row in grid.iter_mut() {
            for x in row.iter_mut() {
                *x = scanner.next();
            }
        }

        let result = spell_casts_num(&grid);
        writeln!(writer, "{}", result).unwrap();
    }

    writer.flush().unwrap();
}
