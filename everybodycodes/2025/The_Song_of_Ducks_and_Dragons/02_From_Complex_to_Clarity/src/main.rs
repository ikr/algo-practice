use std::fmt;
use std::io::{Read, stdin};

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Num(i32, i32);

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

    let parts: Vec<_> = csv.split(',').map(|s| s.parse::<i32>().unwrap()).collect();
    let a = Num(parts[0], parts[1]);

    let mut result = Num(0, 0);
    for _ in 0..3 {
        result = result * result;
        result = result / Num(10, 10);
        result = result + a;
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
