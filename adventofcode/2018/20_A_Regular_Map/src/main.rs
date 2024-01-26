use std::io;

enum Dir {
    N,
    E,
    S,
    W,
}

impl Dir {
    fn decode(c: char) -> Self {
        match c {
            'N' => Dir::N,
            'E' => Dir::E,
            'S' => Dir::S,
            'W' => Dir::W,
            _ => panic!("Invalid Dir {}", c),
        }
    }
}

struct Vert(i32, i32);

impl Vert {
    fn move_to(&self, dir: &Dir) -> Self {
        match dir {
            Dir::N => Vert(self.0, self.1 + 1),
            Dir::E => Vert(self.0 + 1, self.1),
            Dir::S => Vert(self.0, self.1 - 1),
            Dir::W => Vert(self.0 - 1, self.1),
        }
    }
}

fn read_program() -> Vec<char> {
    let mut line = String::new();
    io::stdin().read_line(&mut line).unwrap();
    line.trim().chars().collect()
}

fn main() {
    eprintln!("{:?}", read_program());
}
