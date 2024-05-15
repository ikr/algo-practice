use std::collections::{HashMap, VecDeque};
use std::io::Write;

#[derive(Debug, Clone, Copy)]
struct Trio {
    bitmask: u8,
    indices: [usize; 3],
}

impl Trio {
    fn decode(mut grid_codes: [i16; 3]) -> Trio {
        grid_codes.sort();
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
            assert!(*j < 32);
            if (1 << *j) & xs != 0 {
                sample |= 1 << i;
            }
        }
        (self.bitmask ^ sample).count_ones() <= 1
    }

    fn is_entangled_with(&self, o: &Trio) -> bool {
        self.indices.iter().any(|i| o.indices.contains(i))
    }

    fn is_revealed(&self, revealed: &HashMap<usize, u8>) -> bool {
        self.indices.iter().all(|i| revealed.contains_key(i))
    }

    fn is_bit_set(&self, i: u8) -> bool {
        assert!(i < 3);
        self.bitmask & (1u8 << i) != 0
    }

    fn reveal_new(&self, revealed: &HashMap<usize, u8>) -> Option<(usize, u8)> {
        if self.is_revealed(revealed) {
            return None;
        }

        let [i, j, k] = self.indices;

        if i == j && j == k {
            if (self.bitmask).count_ones() <= 1 {
                Some((i, 0))
            } else {
                assert!((7u8 ^ self.bitmask).count_ones() <= 1);
                Some((i, 1))
            }
        } else if i == j {
            if self.is_bit_set(0) == self.is_bit_set(1) && !revealed.contains_key(&i) {
                if self.is_bit_set(0) {
                    Some((i, 1))
                } else {
                    Some((i, 0))
                }
            } else if self.is_bit_set(0) != self.is_bit_set(1) && !revealed.contains_key(&k) {
                if self.is_bit_set(2) {
                    Some((k, 1))
                } else {
                    Some((k, 0))
                }
            } else {
                None
            }
        } else {
            None
        }
    }
}

fn grid_trios(grid: &[Vec<i16>]) -> Vec<Trio> {
    let n = grid[0].len();
    (0..n)
        .map(|co| Trio::decode([grid[0][co], grid[1][co], grid[2][co]]))
        .collect()
}

fn brute_force_alice_can_win(ts: &[Trio]) -> bool {
    let n = ts.len();
    assert!(n <= 27);
    for xs in 0..(1 << n) {
        if ts.iter().all(|t| t.is_ok_on(xs)) {
            return true;
        }
    }
    false
}

fn alice_can_win(grid: &[Vec<i16>]) -> bool {
    let ts = grid_trios(grid);
    brute_force_alice_can_win(&ts)
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

        let result = if alice_can_win(&grid) { "YES" } else { "NO" };
        writeln!(out, "{}", result).unwrap();
    }
}
