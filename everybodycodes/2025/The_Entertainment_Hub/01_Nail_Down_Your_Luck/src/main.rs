use std::io::{BufRead, stdin};

#[derive(Clone, Copy, Debug)]
enum Dir {
    L,
    R,
}

impl Dir {
    fn decode(x: char) -> Self {
        match x {
            'L' => Self::L,
            'R' => Self::R,
            _ => unreachable!(),
        }
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let isep = lines.iter().position(|s| s.is_empty()).unwrap();

    let grid: Vec<Vec<u8>> = lines[..isep]
        .iter()
        .map(|s| s.chars().map(|c| if c == '*' { 1 } else { 0 }).collect())
        .collect();

    eprintln!("{:?}", grid);

    let programs: Vec<Vec<Dir>> = lines[isep + 1..]
        .iter()
        .map(|s| s.chars().map(Dir::decode).collect())
        .collect();

    eprintln!("{:?}", programs);
}
