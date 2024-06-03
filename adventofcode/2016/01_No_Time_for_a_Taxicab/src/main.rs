#[derive(Clone, Copy)]
enum Turn {
    L,
    R,
}

#[derive(Clone, Copy)]
struct Walk(i32);

#[derive(Clone, Copy)]
struct Hop(Turn, Walk);

fn decode_hop(src: &str) -> Hop {
    Hop(
        match src.chars().next().unwrap() {
            'L' => Turn::L,
            'R' => Turn::R,
            _ => panic!("Invalid turn direction in {}", src),
        },
        Walk(src[1..].parse().unwrap()),
    )
}

#[derive(Clone, Copy)]
struct Crd(i32, i32);

impl Crd {
    fn scaled(&self, k: i32) -> Crd {
        Crd(k * self.0, k * self.1)
    }

    fn distance_from_origin(&self) -> i32 {
        self.0.abs() + self.1.abs()
    }
}

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

#[derive(Clone, Copy)]
enum Dir {
    N,
    E,
    S,
    W,
}

impl Dir {
    fn delta(&self) -> Crd {
        match self {
            Dir::N => Crd(-1, 0),
            Dir::E => Crd(0, 1),
            Dir::S => Crd(1, 0),
            Dir::W => Crd(0, -1),
        }
    }

    fn turn_left(&self) -> Dir {
        match self {
            Dir::N => Dir::W,
            Dir::E => Dir::N,
            Dir::S => Dir::E,
            Dir::W => Dir::S,
        }
    }

    fn turn_right(&self) -> Dir {
        match self {
            Dir::N => Dir::E,
            Dir::E => Dir::S,
            Dir::S => Dir::W,
            Dir::W => Dir::N,
        }
    }
}

fn main() {
    let hops: Vec<Hop> = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim_end()
        .split(", ")
        .map(decode_hop)
        .collect();

    let mut pos = Crd(0, 0);
    let mut dir = Dir::N;

    for Hop(t, Walk(steps)) in hops {
        dir = match t {
            Turn::L => dir.turn_left(),
            Turn::R => dir.turn_right(),
        };

        pos = pos + dir.delta().scaled(steps);
    }

    println!("{}", pos.distance_from_origin());
}
