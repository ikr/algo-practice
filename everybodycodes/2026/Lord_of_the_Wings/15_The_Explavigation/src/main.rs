use std::{
    collections::HashSet,
    io::{BufRead, stdin},
};

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
    fn delta(self) -> Crd {
        match self {
            Dir::N => Crd(-1, 0),
            Dir::E => Crd(0, 1),
            Dir::S => Crd(1, 0),
            Dir::W => Crd(0, -1),
        }
    }

    fn turn_ccw(self) -> Dir {
        match self {
            Dir::N => Dir::W,
            Dir::E => Dir::N,
            Dir::S => Dir::E,
            Dir::W => Dir::S,
        }
    }

    fn turn_cw(self) -> Dir {
        match self {
            Dir::N => Dir::E,
            Dir::E => Dir::S,
            Dir::S => Dir::W,
            Dir::W => Dir::N,
        }
    }
}

#[derive(Debug)]
struct Maze {
    source: Crd,
    sink: Crd,
    walls: HashSet<Crd>,
    deposits: HashSet<Crd>,
}

impl Maze {
    fn new(grid: Vec<Vec<char>>) -> Self {
        let crd_of = |a: char| -> Crd {
            for (i, row) in grid.iter().enumerate() {
                for (j, &cell) in row.iter().enumerate() {
                    if cell == a {
                        return Crd(i as i8, j as i8);
                    }
                }
            }
            unreachable!()
        };

        let [walls, deposits] = grid.iter().enumerate().fold(
            [HashSet::new(), HashSet::new()],
            |[mut ws, mut ds], (i, row)| {
                for (j, &cell) in row.iter().enumerate() {
                    match cell {
                        '#' => ws.insert(Crd(i as i8, j as i8)),
                        '@' => ds.insert(Crd(i as i8, j as i8)),
                        _ => false,
                    };
                }
                [ws, ds]
            },
        );

        Self {
            source: crd_of('S'),
            sink: crd_of('E'),
            walls,
            deposits,
        }
    }

    fn in_bounds(&self, crd: Crd) -> bool {
        let left = self.source.1.min(self.sink.1);
        let right = self.source.1.max(self.sink.1);
        left <= crd.1 && crd.1 <= right
    }
}

fn main() {
    let grid: Vec<Vec<char>> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    eprintln!("{grid:?}\n");
    eprintln!("{:?}", Maze::new(grid));
}
