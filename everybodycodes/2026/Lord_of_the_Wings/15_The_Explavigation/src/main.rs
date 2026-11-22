use std::{
    collections::{HashMap, HashSet, VecDeque},
    io::{BufRead, stdin},
};

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i8, i8);

impl Crd {
    fn from_indices(ro: usize, co: usize) -> Crd {
        Crd(ro as i8, co as i8)
    }
}

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
    fn all() -> [Dir; 4] {
        [Dir::N, Dir::E, Dir::S, Dir::W]
    }

    fn id(self) -> usize {
        Dir::all().into_iter().position(|x| x == self).unwrap()
    }

    fn delta(self) -> Crd {
        match self {
            Dir::N => Crd(-1, 0),
            Dir::E => Crd(0, 1),
            Dir::S => Crd(1, 0),
            Dir::W => Crd(0, -1),
        }
    }

    fn opposite(self) -> Dir {
        match self {
            Dir::N => Dir::S,
            Dir::E => Dir::W,
            Dir::S => Dir::N,
            Dir::W => Dir::E,
        }
    }
}

#[derive(Debug)]
struct Maze {
    height: i8,
    width: i8,
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
                        return Crd::from_indices(i, j);
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
                        '#' => ws.insert(Crd::from_indices(i, j)),
                        '@' => ds.insert(Crd::from_indices(i, j)),
                        _ => false,
                    };
                }
                [ws, ds]
            },
        );

        Self {
            height: grid.len() as i8,
            width: grid[0].len() as i8,
            source: crd_of('S'),
            sink: crd_of('E'),
            walls,
            deposits,
        }
    }

    fn in_bounds(&self, crd: Crd) -> bool {
        0 <= crd.0 && crd.0 < self.height && 0 <= crd.1 && crd.1 < self.width
    }

    fn adjacent(&self, u: (Crd, Dir)) -> Vec<(Crd, Dir)> {
        let (u_crd, u_dir) = u;

        let possible_directions: Vec<_> = Dir::all()
            .into_iter()
            .filter(|&x| x != u_dir.opposite())
            .collect();

        possible_directions
            .into_iter()
            .filter_map(|v_dir| {
                let v_crd = u_crd + v_dir.delta();
                (self.in_bounds(v_crd) && !self.walls.contains(&v_crd)).then_some((v_crd, v_dir))
            })
            .collect()
    }

    fn distances_from(&self, u0: (Crd, Dir)) -> HashMap<(Crd, Dir), u16> {
        assert!(!self.walls.contains(&u0.0));
        assert!(self.in_bounds(u0.0));

        let mut dist: HashMap<(Crd, Dir), u16> = HashMap::from([(u0, 0)]);
        let mut q: VecDeque<(Crd, Dir)> = VecDeque::from([u0]);

        while let Some(u) = q.pop_front() {
            for v in self.adjacent(u) {
                if !dist.contains_key(&v) {
                    dist.insert(v, *dist.get(&u).unwrap() + 1);
                    q.push_back(v);
                }
            }
        }

        dist
    }
}

fn main() {
    let grid: Vec<Vec<char>> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    eprintln!("{grid:?}\n");

    let m = Maze::new(grid);
    eprintln!("{:?}\n", m);

    let dist = m.distances_from((m.source, Dir::E));
    eprintln!("{dist:?}");
}
