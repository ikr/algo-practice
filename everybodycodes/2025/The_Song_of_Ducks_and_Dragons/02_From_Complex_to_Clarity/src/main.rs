use std::fmt;
use std::io::{Read, stdin};

const CAP: i64 = 1_000_000;

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Num(i64, i64);

impl Num {
    fn in_range(self) -> bool {
        self.0.abs() <= CAP && self.1.abs() <= CAP
    }
}

impl std::ops::Add<Num> for Num {
    type Output = Num;

    fn add(self, o: Num) -> Num {
        Num(self.0 + o.0, self.1 + o.1)
    }
}

impl std::ops::Mul<Num> for Num {
    type Output = Num;

    fn mul(self, o: Num) -> Num {
        Num(self.0 * o.0 - self.1 * o.1, self.0 * o.1 + self.1 * o.0)
    }
}

impl std::ops::Div<Num> for Num {
    type Output = Num;

    fn div(self, o: Num) -> Num {
        Num(self.0 / o.0, self.1 / o.1)
    }
}

impl fmt::Display for Num {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "[{},{}]", self.0, self.1)
    }
}

fn main() {
    let mut buffer = String::new();
    stdin().read_to_string(&mut buffer).unwrap();

    let csv = buffer
        .trim()
        .strip_prefix("A=[")
        .unwrap()
        .strip_suffix(']')
        .unwrap();

    let parts: Vec<_> = csv.split(',').map(|s| s.parse::<i64>().unwrap()).collect();
    let top_left = Num(parts[0], parts[1]);
    let bottom_right = top_left + Num(1000, 1000);

    let mut result = 0;
    for y in (top_left.1..=bottom_right.1).step_by(10) {
        for x in (top_left.0..=bottom_right.0).step_by(10) {
            let a = Num(x, y);

            let engrave: bool = || -> bool {
                let mut cur = Num(0, 0);

                for _ in 0..100 {
                    cur = cur * cur;
                    cur = cur / Num(100000, 100000);
                    cur = cur + a;

                    if !cur.in_range() {
                        return false;
                    }
                }
                true
            }();

            if engrave {
                result += 1;
            }
        }
    }
    println!("{result}");
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_num_add() {
        assert_eq!(Num(1, 1) + Num(2, 2), Num(3, 3));
        assert_eq!(Num(-2, 5) + Num(10, -1), Num(8, 4));
    }

    #[test]
    fn test_num_mul() {
        assert_eq!(Num(1, 1) * Num(2, 2), Num(0, 4));
        assert_eq!(Num(2, 5) * Num(3, 7), Num(-29, 29));
        assert_eq!(Num(-2, 5) * Num(10, -1), Num(-15, 52));
        assert_eq!(Num(-1, -2) * Num(-3, -4), Num(-5, 10));
    }

    #[test]
    fn test_num_div() {
        assert_eq!(Num(10, 12) / Num(2, 2), Num(5, 6));
        assert_eq!(Num(11, 12) / Num(3, 5), Num(3, 2));
        assert_eq!(Num(-10, -12) / Num(2, 2), Num(-5, -6));
        assert_eq!(Num(-11, -12) / Num(3, 5), Num(-3, -2));
    }
}
