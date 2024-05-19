use std::{
    fmt::{Display, Formatter, Result},
    io::{self, BufRead},
};

const INITIAL_SOURCE: &str = ".#./..#/###";

struct Tile {
    grid: Vec<Vec<bool>>,
}

impl Tile {
    fn decode_row(source: &str) -> Vec<bool> {
        source
            .chars()
            .map(|x| {
                assert!(x == '.' || x == '#');
                x == '#'
            })
            .collect()
    }

    fn decode(source: &str) -> Tile {
        let grid: Vec<Vec<bool>> = source.split('/').map(Self::decode_row).collect();
        assert!(2 <= grid.len() && grid.len() <= 4);
        assert!(grid.iter().all(|row| row.len() == grid.len()));
        Tile { grid }
    }

    fn to_bits(&self) -> u16 {
        let n = self.grid.len();
        let mut result = 0u16;
        for (ro, row) in self.grid.iter().enumerate() {
            for (co, x) in row.iter().enumerate() {
                if *x {
                    result |= 1u16 << (ro * n + co);
                }
            }
        }
        result
    }

    fn from_bits(n: usize, bits: u16) -> Tile {
        assert!((2..5).contains(&n));
        let mut grid = vec![vec![false; n]; n];
        for shift in 0..(n * n) {
            if bits & (1u16 << shift) != 0 {
                grid[shift / n][shift % n] = true;
            }
        }
        Tile { grid }
    }
}

impl Display for Tile {
    fn fmt(&self, f: &mut Formatter) -> Result {
        let buf: String = self
            .grid
            .iter()
            .map(|row| {
                row.iter()
                    .map(|x| if *x { '#' } else { '.' })
                    .collect::<String>()
            })
            .collect::<Vec<String>>()
            .join("\n");
        write!(f, "{}", buf)
    }
}

fn main() {
    let rule_sides: Vec<(String, String)> = io::stdin()
        .lock()
        .lines()
        .map(|line| {
            let parts: Vec<String> = line.unwrap().split(" => ").map(|x| x.to_string()).collect();
            (parts[0].clone(), parts[1].clone())
        })
        .collect();

    for (a, b) in rule_sides {
        println!("{}\n,\n{}\n\n", Tile::decode(&a), Tile::decode(&b));
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn to_bits_with_the_top_left_set() {
        let t = Tile::decode("#./..");
        assert_eq!(t.to_bits(), 1u16);
    }

    #[test]
    fn to_bits_with_the_bottom_right_set() {
        let t = Tile::decode("..../..../..../...#");
        assert_eq!(t.to_bits(), 32768u16);
    }

    #[test]
    fn to_bits_with_all_set() {
        let t = Tile::decode("###/###/###");
        assert_eq!(t.to_bits(), 511u16);
    }

    #[test]
    fn to_bits_and_back_again() {
        for n in 2..=4 {
            for bits in 0..=((1u32 << (n * n)) - 1) as u16 {
                let t = Tile::from_bits(n, bits);
                assert_eq!(t.grid.len(), n);
                assert_eq!(t.to_bits(), bits);
            }
        }
    }
}
