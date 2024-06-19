use std::collections::{HashSet, VecDeque};

const H: i8 = 4;
const W: i8 = 4;

fn hash(passcode: &str, u: &Vertex) -> String {
    format!("{:x}", md5::compute(passcode.to_owned() + &u.path_string()))
}

fn is_open_door_symbol(hex_digit: u8) -> bool {
    match hex_digit {
        (b'0'..=b'9') | b'a' => false,
        b'b'..=b'f' => true,
        _ => panic!("Invalid hex digit {}", hex_digit),
    }
}

fn open_directions(h: &str) -> Vec<Dir> {
    let [u, d, l, r, ..] = h.chars().collect::<Vec<_>>()[..] else {
        panic!("Can't match a quad prefix in {}", h)
    };

    let src = [(u, Dir::N), (d, Dir::S), (l, Dir::W), (r, Dir::E)];
    src.into_iter()
        .filter(|(digit, _)| is_open_door_symbol(*digit as u8))
        .map(|(_, dir)| dir)
        .collect()
}

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i8, i8);

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

impl Crd {
    fn in_bounds(&self) -> bool {
        let Crd(ro, co) = *self;
        (0..H).contains(&ro) && (0..W).contains(&co)
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

    fn path_string(&self) -> String {
        String::from_utf8(self.path.iter().map(|d| d.as_byte()).collect()).unwrap()
    }

    fn current_crd(&self) -> Crd {
        self.path.iter().fold(Crd(0, 0), |acc, d| acc + d.delta())
    }

    fn possible_directions(&self, passcode: &str) -> Vec<Dir> {
        let crd = self.current_crd();
        open_directions(&hash(passcode, self))
            .into_iter()
            .filter(|d| (crd + d.delta()).in_bounds())
            .collect()
    }

    fn adjacent(&self, passcode: &str) -> Vec<Vertex> {
        self.possible_directions(passcode)
            .into_iter()
            .map(|d| {
                let mut result = self.clone();
                result.path.push(d);
                result
            })
            .collect()
    }

    fn is_terminal(&self) -> bool {
        let Crd(ro, co) = self.current_crd();
        ro == H - 1 && co == W - 1
    }
}

fn main() {
    let passcode: String = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .to_owned();

    let mut visited: HashSet<Vertex> = HashSet::from([Vertex::new()]);
    let mut q: VecDeque<Vertex> = VecDeque::from([Vertex::new()]);

    while let Some(u) = q.pop_front() {
        for v in u.adjacent(&passcode) {
            if !visited.contains(&v) {
                if v.is_terminal() {
                    println!("{}", v.path_string());
                    std::process::exit(0);
                }
                visited.insert(v.clone());
                q.push_back(v);
            }
        }
    }
}
