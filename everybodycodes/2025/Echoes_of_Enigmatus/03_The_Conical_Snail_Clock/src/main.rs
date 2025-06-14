use ac_library::math;
use std::io::{BufRead, stdin};

#[derive(Clone, Copy, Debug)]
struct Coord(i64, i64);

impl Coord {
    fn parse_component(s: &str) -> i64 {
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

    fn disk_diameter(self) -> i64 {
        self.0 + self.1 - 1
    }

    fn phase(self) -> i64 {
        self.0 - 1
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let coords: Vec<Coord> = lines.into_iter().map(|s| Coord::parse(&s)).collect();

    let r: Vec<i64> = coords
        .iter()
        .map(|coord| {
            let d = coord.disk_diameter();
            let p = coord.phase();
            (d - 1 - p + 3 * d) % d
        })
        .collect();

    let m: Vec<i64> = coords
        .into_iter()
        .map(|coord| coord.disk_diameter())
        .collect();

    let result = math::crt(&r, &m).0;
    println!("{}", result);
}
