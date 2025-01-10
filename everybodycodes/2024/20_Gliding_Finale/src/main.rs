use std::{
    collections::{HashMap, HashSet},
    io::{self, BufRead},
};

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i16, i16);

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

impl Crd {
    fn ro(&self) -> usize {
        self.0 as usize
    }

    fn co(&self) -> usize {
        self.1 as usize
    }

    fn from_indices(i: usize, j: usize) -> Crd {
        Crd(i as i16, j as i16)
    }
}

#[derive(Clone, Copy, Debug, Eq, PartialEq)]
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

    fn code(&self) -> usize {
        match self {
            Dir::N => 0,
            Dir::E => 1,
            Dir::S => 2,
            Dir::W => 3,
        }
    }

    fn from_code(code: usize) -> Dir {
        match code {
            0 => Dir::N,
            1 => Dir::E,
            2 => Dir::S,
            3 => Dir::W,
            _ => panic!(),
        }
    }

    fn delta(&self) -> Crd {
        match self {
            Dir::N => Crd(-1, 0),
            Dir::E => Crd(0, 1),
            Dir::S => Crd(1, 0),
            Dir::W => Crd(0, -1),
        }
    }

    fn opposite(&self) -> Dir {
        match self {
            Dir::N => Dir::S,
            Dir::E => Dir::W,
            Dir::S => Dir::N,
            Dir::W => Dir::E,
        }
    }
}

#[derive(Debug)]
struct World {
    blocks: HashSet<Crd>,
    ups: HashSet<Crd>,
    downs: HashSet<Crd>,
    waypoints: HashMap<char, Crd>,
    grid_height: usize,
    grid_width: usize,
}

impl World {
    fn from(grid: &[Vec<char>]) -> Self {
        let mut blocks = HashSet::new();
        let mut ups = HashSet::new();
        let mut downs = HashSet::new();
        let mut waypoints = HashMap::new();

        for (i, row) in grid.iter().enumerate() {
            for (j, cell) in row.iter().enumerate() {
                let p = Crd::from_indices(i, j);
                match cell {
                    '#' => {
                        blocks.insert(p);
                    }
                    '+' => {
                        ups.insert(p);
                    }
                    '-' => {
                        downs.insert(p);
                    }
                    'A' | 'B' | 'C' | 'S' => {
                        waypoints.insert(*cell, p);
                    }
                    _ => {}
                };
            }
        }

        Self {
            blocks,
            ups,
            downs,
            waypoints,
            grid_height: grid.len(),
            grid_width: grid[0].len(),
        }
    }

    fn alt_delta_at(&self, crd: Crd) -> i16 {
        if self.ups.contains(&crd) {
            1
        } else if self.downs.contains(&crd) {
            -2
        } else {
            -1
        }
    }

    fn in_bounds(&self, crd: Crd) -> bool {
        let h = self.grid_height as i16;
        let w = self.grid_width as i16;
        let Crd(r, c) = crd;
        0 <= r && r < h && 0 <= c && c < w
    }

    fn max_possible_altitude(&self) -> i16 {
        let dp0 = vec![vec![vec![None; 4]; self.grid_width]; self.grid_height];

        // dp(i j d) is the max possible altitude at the coordinate (i, j) when facing direction d
        // (0 - North, 1 - East, 2 - South, 3 - West), at the current moment of time.
        let mut dp: Vec<Vec<Vec<Option<i16>>>> = dp0.clone();

        for d in Dir::all() {
            dp[self.waypoints[&'S'].ro()][self.waypoints[&'S'].co()][d.code()] = Some(1000);
        }

        for _ in 1..101 {
            let mut dp_new = dp0.clone();

            for (i, row) in dp.iter().enumerate() {
                for (j, cell) in row.iter().enumerate() {
                    for (dir_code, _) in cell.iter().enumerate() {
                        let dir = Dir::from_code(dir_code);
                        let v = Crd::from_indices(i, j);

                        for (d, u) in Dir::all()
                            .into_iter()
                            .filter(|d| *d != dir.opposite())
                            .map(|d| (d, v + d.delta()))
                            .filter(|(_, p)| self.in_bounds(*p) && !self.blocks.contains(p))
                        {
                            if let Some(a) = dp[u.ro()][u.co()][d.code()] {
                                dp_new[i][j][dir_code] = Some(
                                    dp_new[i][j][dir_code]
                                        .unwrap_or_default()
                                        .max(a + self.alt_delta_at(v)),
                                );
                            }
                        }
                    }
                }
            }

            dp = dp_new;
        }

        dp.into_iter()
            .map(|xs| {
                xs.into_iter()
                    .map(|ys| ys.into_iter().flatten().fold(0, |acc, y| acc.max(y)))
                    .max()
                    .unwrap()
            })
            .max()
            .unwrap()
    }
}

fn main() {
    let grid: Vec<Vec<char>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let world = World::from(&grid);
    eprintln!("{}x{} grid", world.grid_height, world.grid_width);
    println!("{}", world.max_possible_altitude());
}
