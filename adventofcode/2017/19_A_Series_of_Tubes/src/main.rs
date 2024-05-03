use std::io::{self, BufRead};
use std::ops::Add;

#[derive(Debug, Clone, Copy, PartialEq)]
enum Dir {
    N,
    E,
    S,
    W,
}

impl Dir {
    fn opposite(&self) -> Dir {
        match self {
            Dir::N => Dir::S,
            Dir::E => Dir::W,
            Dir::S => Dir::N,
            Dir::W => Dir::E,
        }
    }

    fn all() -> [Dir; 4] {
        [Dir::N, Dir::E, Dir::S, Dir::W]
    }
}

#[derive(Debug, Clone, Copy)]
struct Roco(i32, i32);

impl Add<Roco> for Roco {
    type Output = Roco;

    fn add(self, o: Roco) -> Roco {
        Roco(self.0 + o.0, self.1 + o.1)
    }
}

fn dir_delta(dir: Dir) -> Roco {
    match dir {
        Dir::N => Roco(-1, 0),
        Dir::E => Roco(0, 1),
        Dir::S => Roco(1, 0),
        Dir::W => Roco(0, -1),
    }
}

struct RoutingDiagram {
    grid: Vec<Vec<char>>,
}

type Steps = i32;

impl RoutingDiagram {
    fn column_of_entrance(&self) -> i32 {
        self.grid[0].iter().position(|&x| x == '|').unwrap() as i32
    }

    fn at(&self, roco: Roco) -> char {
        self.grid[roco.0 as usize][roco.1 as usize]
    }

    fn turning_dir(&self, roco: Roco, current_dir: Dir) -> Dir {
        for d in Dir::all() {
            if d == current_dir.opposite() {
                continue;
            }

            let dst = roco + dir_delta(d);
            if self.at(dst) != ' ' {
                return d;
            }
        }

        panic!("Dead end at {:?}", roco)
    }

    fn trace(&self) -> (String, Steps) {
        let mut result = String::new();
        let mut roco = Roco(0, self.column_of_entrance());
        let mut dir = Dir::S;
        let mut steps: Steps = 0;

        loop {
            while self.at(roco) != ' ' && self.at(roco) != '+' {
                roco = roco + dir_delta(dir);
                if self.at(roco).is_alphabetic() {
                    result.push(self.at(roco));
                }
            }

            if self.at(roco) == '+' {
                dir = self.turning_dir(roco, dir);
                roco = roco + dir_delta(dir);
                if self.at(roco).is_alphabetic() {
                    result.push(self.at(roco));
                }
            } else if self.at(roco) == ' ' {
                break;
            }
        }

        (result, steps)
    }
}

fn main() {
    let grid: Vec<Vec<char>> = io::stdin()
        .lock()
        .lines()
        .map(|x| x.unwrap().chars().collect())
        .collect();

    let rd = RoutingDiagram { grid };
    println!("{:?}", rd.trace());
}
