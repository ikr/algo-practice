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

    fn disk_diameter(self) -> u16 {
        self.0 + self.1 - 1
    }

    fn phase(self) -> u16 {
        self.0 - 1
    }

    fn disk_zero(self) -> Coord {
        let x = 1;
        let y = self.1 + self.0 - 1;
        Coord(x, y)
    }

    fn move_k_times(self, k: u64) -> Coord {
        let d = self.disk_diameter() as u64;
        let p0 = self.phase() as u64;
        let p1 = ((p0 + k) % d) as u16;

        let Coord(x0, y0) = self.disk_zero();
        Coord(x0 + p1, y0 - p1)
    }

    fn position_hash(self) -> u64 {
        self.0 as u64 + (100 * (self.1 as u64))
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let coords: Vec<Coord> = lines.into_iter().map(|s| Coord::parse(&s)).collect();

    let hashes: Vec<u64> = coords
        .into_iter()
        .map(|coord| coord.move_k_times(100).position_hash())
        .collect();

    let result: u64 = hashes.into_iter().sum();
    println!("{}", result);
}
