use std::io::{self, BufRead};

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i8, i8);

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

#[derive(Clone, Copy, Debug)]
enum Dir {
    N,
    E,
    S,
    W,
}

impl Dir {
    fn all() -> Vec<Dir> {
        vec![Dir::N, Dir::E, Dir::S, Dir::W]
    }

    fn delta(&self) -> Crd {
        match self {
            Dir::N => Crd(-1, 0),
            Dir::E => Crd(0, 1),
            Dir::S => Crd(1, 0),
            Dir::W => Crd(0, -1),
        }
    }
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().to_string())
        .collect();

    let isep = lines.iter().position(|x| x.is_empty()).unwrap();

    let grid: Vec<Vec<char>> = lines[..isep]
        .iter()
        .map(|x| x.chars().collect::<Vec<_>>())
        .collect::<Vec<_>>();

    let program: String = lines[isep + 1..].join("");

    let (robot_initial, boxes_initial): (Crd, Vec<Crd>) = (|| {
        let mut r = Crd(-1, -1);
        let mut bs = vec![];

        for (i, row) in grid.iter().enumerate() {
            for (j, cell) in row.iter().enumerate() {
                let crd = Crd(i as i8, j as i8);
                match cell {
                    '@' => r = crd,
                    'O' => bs.push(crd),
                    _ => {}
                }
            }
        }

        (r, bs)
    })();

    eprintln!(
        "robot_initial: {:?}, boxes_initial: {:?}",
        robot_initial, boxes_initial
    );
}
