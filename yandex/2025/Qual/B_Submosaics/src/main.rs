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

struct PrefixSum2D {
    xss: Vec<Vec<u32>>,
}

impl PrefixSum2D {
    fn new(mut xss: Vec<Vec<u32>>) -> Self {
        let h = xss.len();
        assert_ne!(h, 0);
        let w = xss[0].len();

        for i in 0..h {
            for j in 0..w {
                if i != 0 {
                    xss[i][j] += xss[i - 1][j];
                }

                if j != 0 {
                    xss[i][j] += xss[i][j - 1];
                }

                if i != 0 && j != 0 {
                    xss[i][j] -= xss[i - 1][j - 1];
                }
            }
        }

        Self { xss }
    }

    fn sigma(&self, r1: usize, c1: usize, r2: usize, c2: usize) -> u32 {
        assert!(r1 <= r2);
        assert!(c1 <= c2);

        let total = self.xss[r2][c2];
        let above = if r1 == 0 { 0 } else { self.xss[r1 - 1][c2] };
        let to_the_left = if c1 == 0 { 0 } else { self.xss[r2][c1 - 1] };
        let both_above_and_to_the_left = if r1 == 0 || c1 == 0 {
            0
        } else {
            self.xss[r1 - 1][c1 - 1]
        };

        (total + both_above_and_to_the_left) - above - to_the_left
    }
}

fn largest_square_size_at(ps: &PrefixSum2D, i: usize, j: usize) -> usize {
    assert_eq!(ps.sigma(i, j, i, j), 1);
    let h = ps.xss.len();
    assert!(i < h);
    let w = ps.xss[0].len();
    assert!(j < w);

    let mut hi: usize = (h - i).min(w - j);
    if ps.sigma(i, j, i + hi - 1, j + hi - 1) as usize == hi * hi {
        return hi;
    }

    let mut lo: usize = 1;
    while lo + 1 != hi {
        let mid = lo + (hi - lo) / 2;
        if ps.sigma(i, j, i + mid - 1, j + mid - 1) as usize == mid * mid {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    lo
}

fn largest_width_at(ps: &PrefixSum2D, i: usize, j: usize, q: usize) -> usize {
    let w = ps.xss[0].len();
    if j + q == w {
        return q;
    }

    let mut hi = w - j;
    if ps.sigma(i, j, i + q - 1, j + hi - 1) as usize == q * hi {
        return hi;
    }

    let mut lo = q;
    while lo + 1 != hi {
        let mid = lo + (hi - lo) / 2;
        if ps.sigma(i, j, i + q - 1, j + mid - 1) as usize == q * mid {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    lo
}

fn largest_height_at(ps: &PrefixSum2D, i: usize, j: usize, q: usize) -> usize {
    let h = ps.xss.len();
    if i + q == h {
        return q;
    }

    let mut hi = h - i;
    if ps.sigma(i, j, i + hi - 1, j + q - 1) as usize == q * hi {
        return hi;
    }

    let mut lo = q;
    while lo + 1 != hi {
        let mid = lo + (hi - lo) / 2;
        if ps.sigma(i, j, i + mid - 1, j + q - 1) as usize == mid * q {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    lo
}

fn coords_of_ones(xss: &[Vec<u32>]) -> Vec<(usize, usize)> {
    let mut result: Vec<(usize, usize)> = vec![];
    for (i, row) in xss.iter().enumerate() {
        for (j, cell) in row.iter().enumerate() {
            if *cell == 1 {
                result.push((i, j));
            }
        }
    }
    result
}

fn max_common_area(aa: Vec<Vec<u32>>, bb: Vec<Vec<u32>>) -> usize {
    let mask = intersection_mask(aa, bb);
    let ones = coords_of_ones(&mask);
    let ps = PrefixSum2D::new(mask);

    ones.into_iter()
        .map(|(i, j)| {
            let q = largest_square_size_at(&ps, i, j);
            let a = largest_height_at(&ps, i, j, q);
            assert!(a >= q);
            let b = largest_width_at(&ps, i, j, q);
            assert!(b >= q);
            a * b
        })
        .max()
        .unwrap_or_default()
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
