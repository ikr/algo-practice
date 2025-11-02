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

fn intersection_mask(aa: Vec<Vec<u32>>, bb: Vec<Vec<u32>>) -> Vec<Vec<u32>> {
    let h = aa.len();
    let w = aa[0].len();
    let mut result = vec![vec![0; w]; h];

    for (i, row) in aa.into_iter().enumerate() {
        for (j, cell) in row.into_iter().enumerate() {
            if cell == bb[i][j] {
                result[i][j] = 1;
            }
        }
    }

    result
}

fn max_common_area(aa: Vec<Vec<u32>>, bb: Vec<Vec<u32>>) -> usize {
    eprintln!("{:?}", intersection_mask(aa, bb));
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
