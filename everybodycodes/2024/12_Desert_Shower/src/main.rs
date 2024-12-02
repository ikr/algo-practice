use std::io::{self, BufRead};

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i32, i32);

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

fn parse_line(s: &str) -> Crd {
    let xs = s
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect::<Vec<_>>();
    Crd(xs[0], xs[1])
}

fn main() {
    let meteors_initial: Vec<Crd> = io::stdin()
        .lock()
        .lines()
        .map(|line| parse_line(&line.unwrap()))
        .collect();

    eprintln!("{:?}", meteors_initial);

    let catapults = vec![Crd(0, 0), Crd(0, 1), Crd(0, 2)];
    eprintln!("{:?}", catapults);
}
