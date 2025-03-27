use std::io::{self, BufRead};

use num_rational::Ratio;
type Frac = Ratio<i128>;

#[derive(Clone, Copy, Debug, PartialEq)]
enum LUnit {
    Shaku,
    Ken,
    Jo,
    Cho,
    Ri,
    Sun,
    Bu,
    Rin,
    Mo,
}

impl LUnit {
    fn from(c: char) -> Self {
        match c {
            '尺' => Self::Shaku,
            '間' => Self::Ken,
            '丈' => Self::Jo,
            '町' => Self::Cho,
            '里' => Self::Ri,
            '寸' => Self::Sun,
            '分' => Self::Bu,
            '厘' => Self::Rin,
            '毛' => Self::Mo,
            _ => panic!("Unknown unit-of-length literal `{}`", c),
        }
    }
}

#[derive(Clone, Copy, Debug, PartialEq)]
struct Length(u64, LUnit);

impl Length {
    fn numeral_values() -> Vec<(char, u64)> {
        vec![
            ('億', 100_000_000),
            ('万', 10_000),
            ('千', 1000),
            ('百', 100),
            ('十', 10),
            ('九', 9),
            ('八', 8),
            ('七', 7),
            ('六', 6),
            ('五', 5),
            ('四', 4),
            ('三', 3),
            ('二', 2),
            ('一', 1),
        ]
    }

    fn decode(cs: &[char]) -> u64 {
        if cs.is_empty() {
            return 0;
        }

        for (numeral, numeral_value) in Self::numeral_values() {
            if let Some(i0) = cs.iter().position(|&x| x == numeral) {
                let pre: u64 = if i0 == 0 {
                    numeral_value
                } else {
                    Self::decode(&cs[..i0]) * numeral_value
                };

                return pre + Self::decode(&cs[i0 + 1..]);
            }
        }

        panic!("/o\\")
    }

    fn from(s: &str) -> Self {
        let cs: Vec<char> = s.chars().collect();
        let n = cs.len();
        Self(Self::decode(&cs[..n - 1]), LUnit::from(cs[n - 1]))
    }

    fn to_shaku(self) -> Frac {
        match self.1 {
            LUnit::Shaku => Frac::from_integer(self.0 as i128),
            LUnit::Ken => Frac::from_integer(6 * self.0 as i128),
            LUnit::Jo => Frac::from_integer(10 * self.0 as i128),
            LUnit::Cho => Frac::from_integer(360 * self.0 as i128),
            LUnit::Ri => Frac::from_integer(12960 * self.0 as i128),
            LUnit::Sun => Frac::new(self.0 as i128, 10),
            LUnit::Bu => Frac::new(self.0 as i128, 100),
            LUnit::Rin => Frac::new(self.0 as i128, 1000),
            LUnit::Mo => Frac::new(self.0 as i128, 10_000),
        }
    }
}

fn decode_line(s: &str) -> (Length, Length) {
    let ab: Vec<_> = s.split(" × ").map(Length::from).collect();
    assert_eq!(ab.len(), 2);
    (ab[0], ab[1])
}

fn main() {
    let lines: Vec<(Length, Length)> = io::stdin()
        .lock()
        .lines()
        .map(|line| decode_line(&line.unwrap()))
        .collect();

    let result: Frac = lines
        .into_iter()
        .map(|(l1, l2)| l1.to_shaku() * l2.to_shaku() * Frac::new(100, 33 * 33))
        .fold(Frac::from_integer(0), |acc, x| acc + x);

    println!("{}", result);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn decode_length_a() {
        assert_eq!(Length::from("二百四十二町"), Length(242, LUnit::Cho));
        assert_eq!(Length::from("三百五十一丈"), Length(351, LUnit::Jo));
    }

    #[test]
    fn decode_length_b() {
        assert_eq!(
            Length::from("九億八千七百六十五万四千三百二十一丈"),
            Length(987_654_321, LUnit::Jo)
        );
    }
}
