use std::io::{BufRead, stdin};

#[derive(Clone, Copy, Debug)]
struct Coord(u16, u16);

impl Coord {
    fn parse_component(s: &str) -> u16 {
        let parts = s.split('=').collect::<Vec<_>>();
        parts[1].parse().unwrap()
    }

    fn parse(s: &str) -> Self {
        let parts = s.split_whitespace().collect::<Vec<_>>();
        Self(
            Self::parse_component(parts[0]),
            Self::parse_component(parts[1]),
        )
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    eprintln!("{:?}", lines);

    let coords: Vec<Coord> = lines.into_iter().map(|s| Coord::parse(&s)).collect();
    eprintln!("{:?}", coords);
}
