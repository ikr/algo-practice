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

#[derive(Clone, Copy, Debug)]
enum TileRowKind {
    Complete,
    LeftPort,
    RightPort,
    LeftRightPort,
}

impl TileRowKind {
    fn infer(xs: &[u8]) -> Self {
        assert!(xs.len() >= 4);

        let b1_mask_and_value_pairs: Vec<(u8, u8)> = vec![
            (0b1000_0000, 0b0000_0000),
            (0b1110_0000, 0b1100_0000),
            (0b1110_0000, 0b1110_0000),
            (0b1111_0000, 0b1111_1000),
        ];

        let i0 = xs
            .iter()
            .position(|&x| b1_mask_and_value_pairs.iter().any(|&(m, v)| m & x == v))
            .unwrap();

        todo!()
    }
}

#[derive(Clone, Debug)]
struct Tile(Vec<Vec<u8>>);

impl Tile {
    fn from_block(xss: &[String]) -> Self {
        let grid: Vec<Vec<u8>> = xss.iter().map(|s| decode_bytes(s)).collect();
        Self(grid)
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

    eprintln!("{:?}\n{} blocks total", blocks, blocks.len());
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_decode_bytes() {
        assert_eq!(decode_bytes(""), vec![]);
        assert_eq!(decode_bytes("7F0120"), vec![127, 1, 32]);
    }
}
