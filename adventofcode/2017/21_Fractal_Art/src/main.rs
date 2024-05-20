use std::{
    collections::HashMap,
    fmt::{Display, Formatter, Result},
    io::{self, BufRead},
};

const INITIAL_SOURCE: &str = ".#./..#/###";

#[derive(Clone, Debug, PartialEq)]
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
        for (i, row) in self.grid.iter().enumerate() {
            for (j, x) in row.iter().enumerate() {
                if *x {
                    result |= 1u16 << (i * n + j);
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

    fn rotate_90_clockwise(&self) -> Tile {
        let n = self.grid.len();
        let mut grid = vec![vec![false; n]; n];

        for (i, row) in self.grid.iter().enumerate() {
            for (j, x) in row.iter().enumerate() {
                if *x {
                    grid[j][n - 1 - i] = true;
                }
            }
        }

        Tile { grid }
    }

    fn reflect_horizontally(&self) -> Tile {
        let grid: Vec<Vec<bool>> = self
            .grid
            .iter()
            .map(|row| {
                let mut result = row.clone();
                result.reverse();
                result
            })
            .collect();
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

#[derive(Debug)]
struct Image {
    size_in_tiles: usize,
    tile_size: usize,
    grid: Vec<Vec<bool>>,
}

impl Image {
    fn new(size_in_tiles: usize, tile_size: usize) -> Image {
        assert!((2..5).contains(&tile_size));
        let n = size_in_tiles * tile_size;
        let grid = vec![vec![false; n]; n];
        Image {
            size_in_tiles,
            tile_size,
            grid,
        }
    }
}

fn main() {
    let rules_map: HashMap<u16, Tile> = io::stdin()
        .lock()
        .lines()
        .map(|line| {
            let parts: Vec<String> = line.unwrap().split(" => ").map(|x| x.to_string()).collect();
            (parts[0].clone(), parts[1].clone())
        })
        .fold(HashMap::new(), |mut acc, (lhs, rhs)| {
            let t1 = Tile::decode(&rhs);
            let mut t0 = Tile::decode(&lhs);
            let mut t0_flipped = t0.reflect_horizontally();
            assert!(!acc.contains_key(&t0.to_bits()));
            assert!(!acc.contains_key(&t0_flipped.to_bits()));

            for _ in 0..4 {
                acc.insert(t0.to_bits(), t1.clone());
                acc.insert(t0_flipped.to_bits(), t1.clone());

                t0 = t0.rotate_90_clockwise();
                t0_flipped = t0_flipped.rotate_90_clockwise();
            }
            acc
        });

    eprintln!("{:?}", rules_map);
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

    #[test]
    fn a_rotation() {
        let t0 = Tile::decode(".#./..#/###");
        let t1 = Tile::decode("#../#.#/##.");
        assert_eq!(t0.rotate_90_clockwise(), t1);
    }

    #[test]
    fn a_horizontal_reflection() {
        let t0 = Tile::decode(".#./..#/###");
        let t1 = Tile::decode(".#./#../###");
        assert_eq!(t0.reflect_horizontally(), t1);
    }

    #[test]
    fn four_rotations_are_an_identity() {
        for n in 2..=4 {
            for bits in 0..=((1u32 << (n * n)) - 1) as u16 {
                let t0 = Tile::from_bits(n, bits);
                let t1 = t0
                    .rotate_90_clockwise()
                    .rotate_90_clockwise()
                    .rotate_90_clockwise()
                    .rotate_90_clockwise();
                assert_eq!(t0, t1);
            }
        }
    }

    #[test]
    fn two_reflections_are_an_identity() {
        for n in 2..=4 {
            for bits in 0..=((1u32 << (n * n)) - 1) as u16 {
                let t0 = Tile::from_bits(n, bits);
                let t1 = t0.reflect_horizontally().reflect_horizontally();
                assert_eq!(t0, t1);
            }
        }
    }
}
