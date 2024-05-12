use std::collections::VecDeque;
use std::io::Write;

#[derive(Debug, Clone, Copy)]
struct Trio {
    bitmask: u8,
    indices: [usize; 3],
}

impl Trio {
    fn decode(grid_codes: [i16; 3]) -> Trio {
        let mut bitmask: u8 = 0;
        let mut indices: [usize; 3] = [0, 0, 0];

        for (i, code) in grid_codes.iter().enumerate() {
            indices[i] = (code.abs() - 1) as usize;
            if *code < 0 {
                bitmask |= 1 << i;
            };
        }

        Trio { bitmask, indices }
    }

    fn is_ok_on(&self, xs: u32) -> bool {
        let mut sample: u8 = 0;
        for (i, j) in self.indices.iter().enumerate() {
            assert!(*j < 33);
            if (1 << *j) & xs != 0 {
                sample |= 1 << i;
            }
        }
        (self.bitmask ^ sample).count_ones() <= 1
    }
}

fn grid_trios(grid: &[Vec<i16>]) -> Vec<Trio> {
    let n = grid[0].len();
    (0..n)
        .map(|co| Trio::decode([grid[0][co], grid[1][co], grid[2][co]]))
        .collect()
}

fn alice_can_win(grid: &[Vec<i16>]) -> bool {
    eprintln!("{:?}", grid_trios(grid));
    false
}

fn main() {
    let mut istream: VecDeque<i16> = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .split_whitespace()
        .map(|x| x.parse::<i16>().unwrap())
        .collect();

    let mut out = std::io::stdout().lock();

    for _ in 0..istream.pop_front().unwrap() {
        let n = istream.pop_front().unwrap() as usize;
        let mut grid: Vec<Vec<i16>> = vec![vec![0; n]; 3];
        for row in grid.iter_mut() {
            for x in row.iter_mut() {
                *x = istream.pop_front().unwrap();
            }
        }

        eprintln!("{:?}", grid);

        let result = if alice_can_win(&grid) { "YES" } else { "NO" };
        writeln!(out, "{}", result).unwrap();
    }
}
