use std::ops;

#[derive(Clone, Copy)]
struct CubeCoord {
    x: i32,
    y: i32,
    z: i32,
}

impl CubeCoord {
    fn distance_to(&self, other: &CubeCoord) -> i32 {
        ((self.x - other.x).abs() + (self.y - other.y).abs() + (self.z - other.z).abs()) / 2
    }
}

impl ops::Add<CubeCoord> for CubeCoord {
    type Output = CubeCoord;

    fn add(self, other: CubeCoord) -> CubeCoord {
        CubeCoord {
            x: self.x + other.x,
            y: self.y + other.y,
            z: self.z + other.z,
        }
    }
}

#[derive(Clone, Copy)]
enum Dir {
    N,
    NE,
    SE,
    S,
    SW,
    NW,
}

impl Dir {
    fn parse(src: &str) -> Dir {
        match src {
            "n" => Dir::N,
            "ne" => Dir::NE,
            "se" => Dir::SE,
            "s" => Dir::S,
            "sw" => Dir::SW,
            "nw" => Dir::NW,
            _ => panic!("Invalid Dir source {}", src),
        }
    }

    fn delta(&self) -> CubeCoord {
        match self {
            Dir::N => CubeCoord { x: 0, y: 1, z: -1 },
            Dir::NE => CubeCoord { x: 1, y: 0, z: -1 },
            Dir::SE => CubeCoord { x: 1, y: -1, z: 0 },
            Dir::S => CubeCoord { x: 0, y: -1, z: 1 },
            Dir::SW => CubeCoord { x: -1, y: 0, z: 1 },
            Dir::NW => CubeCoord { x: -1, y: 1, z: 0 },
        }
    }
}

fn main() {
    let ds: Vec<Dir> = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .split(",")
        .map(Dir::parse)
        .collect();

    let mut loc = CubeCoord { x: 0, y: 0, z: 0 };
    for d in ds.iter() {
        loc = loc + d.delta();
    }
    println!("{}", loc.distance_to(&CubeCoord { x: 0, y: 0, z: 0 }))
}
