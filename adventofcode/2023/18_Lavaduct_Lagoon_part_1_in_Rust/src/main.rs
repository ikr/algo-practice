use std::io::BufRead;

#[derive(Clone, Copy)]
struct Crd(i32, i32);

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;
    fn add(self, other: Crd) -> Crd {
        Crd(self.0 + other.0, self.1 + other.1)
    }
}

#[derive(Debug, PartialEq)]
enum Dir {
    U,
    R,
    D,
    L,
}

impl Dir {
    fn from(s: &str) -> Dir {
        match s {
            "U" => Dir::U,
            "R" => Dir::R,
            "D" => Dir::D,
            "L" => Dir::L,
            _ => panic!("Invalid direction literal `{}`", s),
        }
    }
}

fn parse_line(s: &str) -> (Dir, i32) {
    let parts = s.split_whitespace().collect::<Vec<_>>();
    (Dir::from(parts[0]), parts[1].parse().unwrap())
}

fn main() {
    let lines: Vec<String> = std::io::stdin()
        .lock()
        .lines()
        .map(|a| a.unwrap().to_string())
        .collect();

    let instructions = lines
        .into_iter()
        .map(|s| parse_line(&s))
        .collect::<Vec<_>>();

    eprintln!("{:?}", instructions);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn parse_line_works() {
        assert_eq!(parse_line("R 10 (#508fe2)"), (Dir::R, 10));
    }

    #[test]
    fn dir_from_works() {}
}
