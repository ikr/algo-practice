use itertools::Itertools;
use std::{
    collections::{HashMap, HashSet, VecDeque, hash_map::Entry},
    io::{BufRead, stdin},
};

const NUM_TARGET_DEPOSITS: usize = 2026;

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

struct Maze {
    height: i8,
    width: i8,
    source: Crd,
    sink: Crd,
    walls: HashSet<Crd>,
    deposits: Vec<Crd>,
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

        let (walls, deposits) =
            grid.iter()
                .enumerate()
                .fold((HashSet::new(), vec![]), |(mut ws, mut ds), (i, row)| {
                    for (j, &cell) in row.iter().enumerate() {
                        match cell {
                            '#' => {
                                ws.insert(Crd::from_indices(i, j));
                            }
                            '@' => {
                                ds.push(Crd::from_indices(i, j));
                            }
                            _ => {}
                        };
                    }
                    (ws, ds)
                });

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

    fn shortest_path(&self, a: (Crd, Dir), b: (Crd, Dir)) -> Vec<(Crd, Dir)> {
        assert!(!self.walls.contains(&a.0));
        assert!(!self.walls.contains(&b.0));

        let mut pre: HashMap<(Crd, Dir), (Crd, Dir)> = HashMap::from([(a, a)]);
        let mut q: VecDeque<(Crd, Dir)> = VecDeque::from([a]);

        while let Some(u) = q.pop_front() {
            if u == b {
                break;
            }

            for v in self.adjacent(u) {
                if let Entry::Vacant(e) = pre.entry(v) {
                    e.insert(u);
                    q.push_back(v);
                }
            }
        }

        if !pre.contains_key(&b) {
            return vec![];
        }

        let mut result = vec![b];
        let mut cur = b;

        while cur != a {
            cur = pre[&cur];
            result.push(cur);
        }

        result.reverse();
        result
    }

    fn path_yield(&self, path: &[(Crd, Dir)]) -> usize {
        path.iter()
            .filter(|(crd, _)| self.deposits.contains(crd))
            .count()
    }

    fn min_time_to_collect_enough_deposits(&self, cycle: &[(Crd, Dir)]) -> usize {
        let cycle_yield = self.path_yield(cycle);
        let main_deposit = *cycle.first().unwrap();

        let pre = self.shortest_path((self.source, Dir::E), main_deposit);
        let pre_yield = self.path_yield(&pre);

        let post = self.shortest_path(main_deposit, (self.sink, Dir::E));
        let post_yield = self.path_yield(&post);

        let total_time = |k: usize| -> usize { pre.len() - 1 + k * cycle.len() + post.len() - 1 };
        let total_yield = |k: usize| -> usize { pre_yield + k * cycle_yield + post_yield };

        let mut num_cycles: usize = 1;
        while total_yield(num_cycles) < NUM_TARGET_DEPOSITS {
            num_cycles += 1;
        }
        total_time(num_cycles)
    }
}

fn main() {
    let grid: Vec<Vec<char>> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let maze = Maze::new(grid);

    let cycles: Vec<Vec<(Crd, Dir)>> = maze
        .deposits
        .iter()
        .cartesian_product(Dir::all())
        .filter_map(|(&crd, dir)| {
            if maze.walls.contains(&(crd + dir.delta())) {
                None
            } else {
                let u = (crd, dir.opposite());
                let v = (crd + dir.delta(), dir.opposite());
                let path = maze.shortest_path(u, v);
                (!path.is_empty()).then_some(path)
            }
        })
        .collect();

    let best_cycle = cycles
        .iter()
        .min_by_key(|cycle| maze.min_time_to_collect_enough_deposits(cycle))
        .unwrap();

    let result = cycles
        .into_iter()
        .map(|cycle| maze.min_time_to_collect_enough_deposits(&cycle))
        .min()
        .unwrap();

    println!("{result}");
}
