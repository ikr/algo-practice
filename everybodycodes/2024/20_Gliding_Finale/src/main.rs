use std::{
    collections::{HashMap, HashSet},
    io::{self, BufRead},
};

use memoize::memoize;

const T_HORIZON: u16 = 200;

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

#[derive(Clone, Copy, Debug, Eq, PartialEq, Hash)]
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
    start: Crd,
    grid_height: usize,
    grid_width: usize,
}

impl World {
    fn from(grid: &[Vec<char>]) -> Self {
        let mut blocks = HashSet::new();
        let mut ups = HashSet::new();
        let mut downs = HashSet::new();
        let mut start = Crd(-1, -1);

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
                    'S' => {
                        start = p;
                    }
                    _ => {}
                };
            }
        }

        Self {
            blocks,
            ups,
            downs,
            start,
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
}

fn group_by_t_and_alt(tris: Vec<(Dir, u16, i16)>) -> Vec<(Vec<Dir>, u16, i16)> {
    let xs: HashMap<(u16, i16), Vec<Dir>> =
        tris.into_iter()
            .fold(HashMap::new(), |mut acc, (dir, t, alt)| {
                acc.entry((t, alt))
                    .and_modify(|dirs| dirs.push(dir))
                    .or_insert(vec![dir]);
                acc
            });

    let mut result: Vec<(Vec<Dir>, u16, i16)> = xs
        .into_iter()
        .map(|((t, alt), dirs)| (dirs, t, alt))
        .collect();

    result.sort_by_key(|(_, t, alt)| (*t, -*alt));
    result
}

#[memoize(Ignore: world)]
fn arrival_possibilities(
    world: &World,
    src_crd: Crd,
    src_dirs: Vec<Dir>,
    dst_crd: Crd,
) -> Vec<(Dir, u16, i16)> {
    let dp0 = vec![vec![vec![None; 4]; world.grid_width]; world.grid_height];

    // dp(i j d) is the max possible altitude at the coordinate (i, j) when facing direction d
    // (0 - North, 1 - East, 2 - South, 3 - West), at the current moment of time.
    let mut dp: Vec<Vec<Vec<Option<i16>>>> = dp0.clone();

    for d in src_dirs {
        dp[src_crd.ro()][src_crd.co()][d.code()] = Some(0);
    }

    let mut result = vec![];

    for t in 1..=T_HORIZON {
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
                        .filter(|(_, p)| world.in_bounds(*p) && !world.blocks.contains(p))
                    {
                        if let Some(a) = dp[u.ro()][u.co()][d.code()] {
                            dp_new[i][j][dir_code] = Some(
                                dp_new[i][j][dir_code]
                                    .unwrap_or(i16::MIN)
                                    .max(a + world.alt_delta_at(v)),
                            );
                        }
                    }

                    if v == dst_crd {
                        if let Some(a) = dp_new[i][j][dir_code] {
                            result.push((dir, t, a));
                        }
                    }
                }
            }
        }

        dp = dp_new;
    }

    result
}

fn main() {
    let grid: Vec<Vec<char>> = io::stdin()
        .lock()
        .lines()
        .map(|line| {
            let s = line.unwrap();
            s.chars().take(s.len() - 1).skip(1).collect()
        })
        .collect();

    let world = World::from(&grid);
    eprintln!(
        "{}x{} grid\n{:?}",
        world.grid_height, world.grid_width, grid
    );
}
