#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i32, i32);

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
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

    fn as_byte(&self) -> u8 {
        match self {
            Dir::N => b'U',
            Dir::E => b'R',
            Dir::S => b'D',
            Dir::W => b'L',
        }
    }
}

#[derive(Clone, Debug, Eq, Hash, PartialEq)]
struct Vertex {
    path: Vec<Dir>,
}

impl Vertex {
    fn new() -> Vertex {
        Vertex { path: vec![] }
    }

    fn current_crd(&self) -> Crd {
        self.path.iter().fold(Crd(0, 0), |acc, d| acc + d.delta())
    }
}

fn main() {
    let passcode: String = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .to_owned();
    eprintln!("The pass code given is {}", passcode);
}
