use std::io::{self, BufRead};

#[derive(Clone, Copy, Debug)]
enum LUnit {
    Shaku,
    Ken,
    Jo,
    Cho,
    Ri,
}

impl LUnit {
    fn from(c: char) -> Self {
        match c {
            '尺' => Self::Shaku,
            '間' => Self::Ken,
            '丈' => Self::Jo,
            '町' => Self::Cho,
            '里' => Self::Ri,
            _ => panic!("Unknown unit-of-length literal `{}`", c),
        }
    }
}

#[derive(Clone, Copy, Debug)]
struct Length(u64, LUnit);

impl Length {
    fn parse_num(s: String) -> u64 {
        todo!()
    }

    fn from(s: &str) -> Self {
        let cs: Vec<char> = s.chars().collect();
        let n = cs.len();
        Self(
            Self::parse_num(cs[..n - 1].iter().cloned().collect::<String>()),
            LUnit::from(cs[n - 1]),
        )
    }

    fn to_shaku(&self) -> u64 {
        match self.1 {
            LUnit::Shaku => self.0,
            LUnit::Ken => 6 * self.0,
            LUnit::Jo => 6 * 10 * self.0,
            LUnit::Cho => 6 * 10 * 360 * self.0,
            LUnit::Ri => 6 * 10 * 360 * 12960 * self.0,
        }
    }
}

fn parse_line(s: &str) -> (Length, Length) {
    let ab: Vec<_> = s.split(" × ").map(Length::from).collect();
    assert_eq!(ab.len(), 2);
    (ab[0], ab[1])
}

fn main() {
    let lines: Vec<(Length, Length)> = io::stdin()
        .lock()
        .lines()
        .map(|line| parse_line(&line.unwrap()))
        .collect();

    let result: u64 = lines
        .into_iter()
        .map(|(l1, l2)| l1.to_shaku() * l2.to_shaku() * 33 * 33 / 10 / 10)
        .sum();

    println!("{}", result);
}
