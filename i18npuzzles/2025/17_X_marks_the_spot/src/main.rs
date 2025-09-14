use std::io::{BufRead, stdin};

/*
+------------+------------+-----------+-----------+-----------+-----------+
| First CP   | Last CP    | Byte 1    | Byte 2    | Byte 3    | Byte 4    |
+------------+------------+-----------+-----------+-----------+-----------+
| U+0000     | U+007F     | 0yyyzzzz  |           |           |           |
| U+0080     | U+07FF     | 110xxxyy  | 10yyzzzz  |           |           |
| U+0800     | U+FFFF     | 1110wwww  | 10xxxxyy  | 10yyzzzz  |           |
| U+010000   | U+10FFFF   | 11110uvv  | 10vvwwww  | 10xxxxyy  | 10yyzzzz  |
+------------+------------+-----------+-----------+-----------+-----------+
*/

fn b1_mask_and_value_pairs() -> Vec<(u8, u8)> {
    vec![
        (0b1000_0000, 0b0000_0000),
        (0b1110_0000, 0b1100_0000),
        (0b1111_0000, 0b1110_0000),
        (0b1111_1000, 0b1111_0000),
    ]
}

#[derive(Clone, Debug, PartialEq)]
struct SplitB(Vec<u8>);

impl SplitB {
    fn detect(xs: &[u8]) -> Option<Self> {
        let i0 = xs
            .iter()
            .position(|&x| {
                b1_mask_and_value_pairs()
                    .into_iter()
                    .any(|(m, v)| m & x == v)
            })
            .unwrap();

        if i0 == 0 {
            None
        } else {
            Some(Self(xs[..i0].to_vec()))
        }
    }
}

#[derive(Clone, Debug, PartialEq)]
struct SplitA(Vec<u8>);

impl SplitA {
    fn multibyte_seq_len(b1: u8) -> usize {
        let j = b1_mask_and_value_pairs()
            .into_iter()
            .position(|(m, v)| m & b1 == v)
            .unwrap();
        j + 1
    }

    fn split_tail(xs: &[u8]) -> Vec<u8> {
        if let Some(&x0) = xs.first() {
            let l = Self::multibyte_seq_len(x0);
            if l <= xs.len() {
                Self::split_tail(&xs[l..])
            } else {
                xs.to_vec()
            }
        } else {
            vec![]
        }
    }

    fn detect(xs: &[u8]) -> Option<Self> {
        let i0: usize = if let Some(SplitB(bb)) = SplitB::detect(xs) {
            bb.len()
        } else {
            0
        };
        let aa = Self::split_tail(&xs[i0..]);
        if aa.is_empty() { None } else { Some(Self(aa)) }
    }

    fn missing_len(&self) -> usize {
        assert!(!self.0.is_empty());
        Self::multibyte_seq_len(self.0[0]) - self.0.len()
    }
}

#[derive(Clone, Debug)]
struct Tile(Vec<Vec<u8>>);

impl Tile {
    fn decode_bytes(s: &str) -> Vec<u8> {
        s.chars()
            .collect::<Vec<_>>()
            .chunks(2)
            .map(|xy| {
                assert_eq!(xy.len(), 2);
                let buf: String = xy.iter().collect();
                u8::from_str_radix(&buf, 16).unwrap()
            })
            .collect()
    }

    fn from_block(xss: &[String]) -> Self {
        let grid: Vec<Vec<u8>> = xss.iter().map(|s| Self::decode_bytes(s)).collect();
        Self(grid)
    }

    fn left_edge(&self) -> Vec<Option<SplitB>> {
        self.0.iter().map(|row| SplitB::detect(row)).collect()
    }

    fn right_edge(&self) -> Vec<Option<SplitA>> {
        self.0.iter().map(|row| SplitA::detect(row)).collect()
    }

    fn is_left_top_corner(&self) -> bool {
        let needle: Vec<u8> = "╔".bytes().collect();

        self.0[0]
            .windows(needle.len())
            .position(|xs| xs == needle)
            .is_some_and(|i| i == 0)
    }

    fn lhs_pluggable_into(&self, other: &Self, my_vert_offset_across_other: usize) -> bool {
        let my_edge = self.right_edge();
        let other_edge: Vec<_> = other.left_edge();
        assert!(my_vert_offset_across_other < other_edge.len());

        my_edge
            .into_iter()
            .zip(other_edge.into_iter().skip(my_vert_offset_across_other))
            .all(|(mb_a, mb_b)| match (mb_a, mb_b) {
                (Some(a), Some(b)) => a.missing_len() == b.0.len(),
                (None, Some(_)) => false,
                (Some(_), None) => false,
                _ => true,
            })
    }

    fn rhs_pluggable_into(&self, other: &Self, my_vert_offset_across_other: usize) -> bool {
        let my_edge = self.left_edge();
        let other_edge: Vec<_> = other.right_edge();
        assert!(my_vert_offset_across_other < other_edge.len());

        other_edge
            .into_iter()
            .skip(my_vert_offset_across_other)
            .zip(my_edge)
            .all(|(mb_a, mb_b)| match (mb_a, mb_b) {
                (Some(a), Some(b)) => a.missing_len() == b.0.len(),
                (None, Some(_)) => false,
                (Some(_), None) => false,
                _ => true,
            })
    }
}

#[derive(Clone)]
struct Paste {
    tile: Tile,
    irow: usize,
    icol: usize,
}

impl Paste {
    fn new(tile: Tile, irow: usize, icol: usize) -> Self {
        Self { tile, irow, icol }
    }
}

#[derive(Clone, Copy)]
enum Port {
    None,
    A {
        paste_index: usize,
        vert_offset: usize,
    },
    B {
        paste_index: usize,
        vert_offset: usize,
    },
}

struct Grid {
    pastes: Vec<Paste>,
    bytes: Vec<Vec<Option<u8>>>,
    ports: Vec<Vec<Port>>,
}

impl Grid {
    const H: usize = 50;
    const W: usize = 550;

    fn new() -> Self {
        Self {
            pastes: vec![],
            bytes: vec![vec![None; Self::W]; Self::H],
            ports: vec![vec![Port::None; Self::W]; Self::H],
        }
    }

    fn paste_at(&mut self, tile: Tile, i0: usize, j0: usize) {
        for (i, row) in tile.0.iter().enumerate() {
            for (j, x) in row.iter().enumerate() {
                assert!(self.bytes[i0 + i][j0 + j].is_none());
                self.bytes[i0 + i][j0 + j] = Some(*x);
            }
        }

        let h = tile.0.len();
        let w = tile.0[0].len();
        let paste_index = self.pastes.len();
        self.pastes.push(Paste::new(tile, i0, j0));

        for vert_offset in 0..h {
            if j0 != 0 {
                self.ports[i0 + vert_offset][j0 - 1] = Port::B {
                    paste_index,
                    vert_offset,
                }
            }

            if j0 + w != Self::W {
                self.ports[i0 + vert_offset][j0 + w] = Port::A {
                    paste_index,
                    vert_offset,
                }
            }
        }
    }

    fn eprint_atlas(&self) {
        let mut raster: Vec<Vec<char>> = vec![vec![' '; Self::W]; Self::H];

        for Paste { tile, irow, icol } in &self.pastes {
            for (i, row) in tile.0.iter().enumerate() {
                for (j, _) in row.iter().enumerate() {
                    raster[irow + i][icol + j] = '.';
                }
            }

            for (i, mbx) in tile.left_edge().into_iter().enumerate() {
                if let Some(x) = mbx {
                    let k = x.0.len();
                    for j in 0..k {
                        raster[irow + i][icol + j] = '=';
                    }
                }
            }

            for (i, mbx) in tile.right_edge().into_iter().enumerate() {
                if let Some(x) = mbx {
                    let k = x.0.len();
                    let w = tile.0[0].len();
                    for j in w - k..w {
                        raster[irow + i][icol + j] = '-';
                    }
                }
            }
        }

        for row in raster {
            let s: String = row.into_iter().collect();
            eprintln!("{s}");
        }
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();

    let blocks: Vec<Vec<String>> = lines.into_iter().fold(vec![], |mut acc, line| {
        match (acc.last_mut(), line.as_str()) {
            (Some(_), "") => {
                acc.push(vec![]);
                acc
            }
            (None, "") => unreachable!(),
            (None, _) => {
                acc.push(vec![line]);
                acc
            }
            (Some(last), _) => {
                last.push(line);
                acc
            }
        }
    });

    let mut tiles: Vec<Tile> = blocks.into_iter().map(|b| Tile::from_block(&b)).collect();
    eprintln!("Initial number of tiles: {}", tiles.len());
    assert_eq!(tiles.iter().filter(|t| t.is_left_top_corner()).count(), 1);

    let left_top_tile: Tile = {
        let it = tiles.iter().position(|t| t.is_left_top_corner()).unwrap();
        tiles.remove(it)
    };
    assert!(left_top_tile.left_edge().into_iter().all(|x| x.is_none()));

    let mut grid: Grid = Grid::new();
    let mut pre = left_top_tile.clone();
    grid.paste_at(left_top_tile, 0, 0);

    let mut j0 = pre.0[0].len();

    loop {
        assert_eq!(
            tiles
                .iter()
                .filter(|t| pre.lhs_pluggable_into(t, 0))
                .count(),
            1
        );

        let it = tiles
            .iter()
            .position(|t| pre.lhs_pluggable_into(t, 0))
            .unwrap();

        let tile = tiles.remove(it);
        pre = tile.clone();

        let w = tile.0[0].len();
        grid.paste_at(tile, 0, j0);
        j0 += w;

        if pre.right_edge().into_iter().all(|x| x.is_none()) {
            break;
        }
    }

    grid.eprint_atlas();
    eprintln!("Remaining number of tiles: {}", tiles.len());
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_decode_bytes() {
        assert_eq!(Tile::decode_bytes(""), vec![]);
        assert_eq!(Tile::decode_bytes("7F0120"), vec![127, 1, 32]);
    }

    #[test]
    fn test_detection_of_a_suffix_of_a_horizontal_split() {
        for (src, expected) in [
            ("e295902de295902de295902de295902d", None),
            ("7ec3b1f091808de2898bc3b17e7ec3b1", None),
            (
                "91808d7ee2898b7ec3b1c3b17ec3b17e",
                Some(SplitB(vec![0x91, 0x80, 0x8D])),
            ),
            (
                "91808d2dc2af7ec3b1c3b1c3b1c3b1c3",
                Some(SplitB(vec![0x91, 0x80, 0x8D])),
            ),
            ("b1c3b1c3b1e288922dc2afc2afc3b17c", Some(SplitB(vec![0xB1]))),
        ] {
            assert_eq!(
                SplitB::detect(&Tile::decode_bytes(src)),
                expected,
                "Failed on {}",
                src
            );
        }
    }

    #[test]
    fn test_detection_of_a_prefix_of_a_horizontal_split() {
        for (src, expected) in [
            ("e295902de295902de295902de295902d", None),
            ("7ec3b1f091808de2898bc3b17e7ec3b1", None),
            ("e29591c3b1c3b1e2898b7e7ee2898bf0", Some(SplitA(vec![0xF0]))),
            ("91808d2dc2af7ec3b1c3b1c3b1c3b1c3", Some(SplitA(vec![0xC3]))),
        ] {
            assert_eq!(
                SplitA::detect(&Tile::decode_bytes(src)),
                expected,
                "Failed on {}",
                src
            );
        }
    }

    #[test]
    fn test_horizontal_split_a_missing_len() {
        assert_eq!(SplitA(vec![0xC3]).missing_len(), 1);
        assert_eq!(SplitA(vec![0xF0]).missing_len(), 3);
    }

    #[test]
    fn test_pluggable_into() {
        let aa = Tile::from_block(&[
            "e295942de295902de295902de295902d".to_string(),
            "7c7ee2898be2898bc3b1c3b1e2898b7e".to_string(),
            "e29591c3b1c3b1e2898b7e7ee2898bf0".to_string(),
            "7c7ec3b1c3b1f091808dc3b1e2898bf0".to_string(),
        ]);

        let bb = Tile::from_block(&[
            "e295902de295902de295902de295902d".to_string(),
            "7ec3b1f091808de2898bc3b17e7ec3b1".to_string(),
            "91808d7ee2898b7ec3b1c3b17ec3b17e".to_string(),
            "91808d2dc2af7ec3b1c3b1c3b1c3b1c3".to_string(),
        ]);

        let cc = Tile::from_block(&[
            "2de295902de295902de295902de29597".to_string(),
            "e2898b7ec3b1c3b1f091808d7ec3b17c".to_string(),
            "c3b1c3b1c3b1e2898bc3b17e7ee29591".to_string(),
            "b1c3b1c3b1e288922dc2afc2afc3b17c".to_string(),
            "808de2898bc3b12d2d2d2dc3b1e29591".to_string(),
            "808dc3b1c2afc2afe28892c2af2d7e7c".to_string(),
            "8de2898b7ec2af2d2dc3b1c3b1e29591".to_string(),
            "898b7ec3b1e2898bc2afe2898b7e7e7c".to_string(),
        ]);

        assert!(!aa.lhs_pluggable_into(&cc, 0));

        assert!(aa.lhs_pluggable_into(&bb, 0));
        assert!(bb.rhs_pluggable_into(&aa, 0));

        assert!(bb.lhs_pluggable_into(&cc, 0));
        assert!(cc.rhs_pluggable_into(&bb, 0));

        assert!(!bb.rhs_pluggable_into(&aa, 2));
        assert!(!aa.lhs_pluggable_into(&bb, 1));
        assert!(!bb.lhs_pluggable_into(&cc, 1));
    }
}
