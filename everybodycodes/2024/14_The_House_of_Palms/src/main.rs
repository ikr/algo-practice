use std::io::Read;

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i32, i32, i32);

impl Crd {
    fn mul_by(&self, n: i32) -> Crd {
        Crd(self.0 * n, self.1 * n, self.2 * n)
    }
}

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1, self.2 + o.2)
    }
}

#[derive(Clone, Copy, Debug)]
enum Dir {
    U,
    D,
    L,
    R,
    F,
    B,
}

impl Dir {
    fn new(src: char) -> Self {
        match src {
            'U' => Dir::U,
            'D' => Dir::D,
            'L' => Dir::L,
            'R' => Dir::R,
            'F' => Dir::F,
            'B' => Dir::B,
            _ => panic!("Invalid direction {}", src),
        }
    }

    fn delta(&self) -> Crd {
        match self {
            Dir::U => Crd(0, 0, 1),
            Dir::D => Crd(0, 0, -1),
            Dir::L => Crd(-1, 0, 0),
            Dir::R => Crd(1, 0, 0),
            Dir::F => Crd(0, 1, 0),
            Dir::B => Crd(0, -1, 0),
        }
    }
}

fn parse_command(s: &str) -> (Dir, u32) {
    let chars = s.chars().collect::<Vec<_>>();
    (
        Dir::new(chars[0]),
        chars[1..].iter().collect::<String>().parse().unwrap(),
    )
}

fn main() {
    let mut buf: String = String::new();
    std::io::stdin().read_to_string(&mut buf).unwrap();

    let commands = buf
        .trim_end()
        .split(',')
        .map(parse_command)
        .collect::<Vec<_>>();

    let mut result: i32 = 0;
    let mut cur = Crd(0, 0, 0);
    for (dir, l) in commands {
        cur = cur + dir.delta().mul_by(l as i32);
        result = result.max(cur.2);
    }
    println!("{}", result);
}
