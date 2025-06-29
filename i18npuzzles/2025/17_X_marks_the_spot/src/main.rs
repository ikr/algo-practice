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

fn b1_mask_and_value_pairs() -> Vec<(u8, u8)> {
    vec![
        (0b1000_0000, 0b0000_0000),
        (0b1110_0000, 0b1100_0000),
        (0b1111_0000, 0b1110_0000),
        (0b1111_1000, 0b1111_0000),
    ]
}

#[derive(Clone, Debug, PartialEq)]
struct HSplitB(Vec<u8>);

impl HSplitB {
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
struct HSplitA(Vec<u8>);

impl HSplitA {
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
        let i0: usize = if let Some(HSplitB(bb)) = HSplitB::detect(xs) {
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
    fn from_block(xss: &[String]) -> Self {
        let grid: Vec<Vec<u8>> = xss.iter().map(|s| decode_bytes(s)).collect();
        Self(grid)
    }

    fn left_edge(&self) -> Vec<Option<HSplitB>> {
        self.0.iter().map(|row| HSplitB::detect(row)).collect()
    }

    fn right_edge(&self) -> Vec<Option<HSplitA>> {
        self.0.iter().map(|row| HSplitA::detect(row)).collect()
    }

    fn is_left_top_corner(&self) -> bool {
        let needle: Vec<u8> = "╔".bytes().collect();

        self.0[0]
            .windows(needle.len())
            .position(|xs| xs == needle)
            .is_some_and(|i| i == 0)
    }

    fn can_be_left_neigh(&self, other: &Self, vert_offset: usize) -> bool {
        todo!()
    }

    fn can_be_right_neigh(&self, other: &Self, vert_offset: usize) -> bool {
        todo!()
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

    let mut heights: Vec<usize> = blocks.iter().map(|b| b.len()).collect();
    heights.sort();
    eprintln!("Heights: {heights:?}");

    for block in blocks.iter() {
        let t = Tile::from_block(block);
        eprintln!(
            "{:?}",
            t.right_edge().into_iter().flatten().collect::<Vec<_>>()
        );
    }

    let left_tops_count = blocks
        .into_iter()
        .filter_map(|block| {
            let t = Tile::from_block(&block);
            if t.is_left_top_corner() {
                Some(true)
            } else {
                None
            }
        })
        .count();

    dbg!(left_tops_count);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_decode_bytes() {
        assert_eq!(decode_bytes(""), vec![]);
        assert_eq!(decode_bytes("7F0120"), vec![127, 1, 32]);
    }

    #[test]
    fn test_detection_of_a_suffix_of_a_horizontal_split() {
        for (src, expected) in [
            ("e295902de295902de295902de295902d", None),
            ("7ec3b1f091808de2898bc3b17e7ec3b1", None),
            (
                "91808d7ee2898b7ec3b1c3b17ec3b17e",
                Some(HSplitB(vec![0x91, 0x80, 0x8D])),
            ),
            (
                "91808d2dc2af7ec3b1c3b1c3b1c3b1c3",
                Some(HSplitB(vec![0x91, 0x80, 0x8D])),
            ),
            (
                "b1c3b1c3b1e288922dc2afc2afc3b17c",
                Some(HSplitB(vec![0xB1])),
            ),
        ] {
            assert_eq!(
                HSplitB::detect(&decode_bytes(src)),
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
            (
                "e29591c3b1c3b1e2898b7e7ee2898bf0",
                Some(HSplitA(vec![0xF0])),
            ),
            (
                "91808d2dc2af7ec3b1c3b1c3b1c3b1c3",
                Some(HSplitA(vec![0xC3])),
            ),
        ] {
            assert_eq!(
                HSplitA::detect(&decode_bytes(src)),
                expected,
                "Failed on {}",
                src
            );
        }
    }

    #[test]
    fn test_horizontal_split_a_missing_len() {
        assert_eq!(HSplitA(vec![0xC3]).missing_len(), 1);
        assert_eq!(HSplitA(vec![0xF0]).missing_len(), 3);
    }
}
