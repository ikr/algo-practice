use std::{
    collections::HashSet,
    io::{self, BufRead},
};

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i32, i32);

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
        Crd(i as i32, j as i32)
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
struct WorldTile {
    blocks: HashSet<Crd>,
    ups: HashSet<Crd>,
    downs: HashSet<Crd>,
    start: Crd,
    height: usize,
    width: usize,
}

impl WorldTile {
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
            height: grid.len(),
            width: grid[0].len(),
        }
    }

    fn alt_delta_at(&self, crd: Crd) -> i32 {
        if self.ups.contains(&crd) {
            1
        } else if self.downs.contains(&crd) {
            -2
        } else {
            -1
        }
    }

    fn in_bounds(&self, crd: Crd) -> bool {
        let h = self.height as i32;
        let w = self.width as i32;
        let Crd(r, c) = crd;
        0 <= r && r <= h && 0 <= c && c < w
    }

    fn max_flight_altitudes(&self, start_row: &[Vec<Option<i32>>]) -> Vec<Vec<Vec<Option<i32>>>> {
        // dp(i j d) is the max possible altitude at the coordinate (i, j) when facing direction d
        // (0 - North, 1 - East, 2 - South, 3 - West), at the current moment of time.
        let mut dp: Vec<Vec<Vec<Option<i32>>>> =
            vec![vec![vec![None; Dir::all().len()]; self.width]; self.height + 1];
        dp[0] = start_row.to_vec();
        let t_horizon = self.width;

        for _ in 0..t_horizon {
            let mut dp_new = dp.clone();

            for (i, row) in dp.iter().enumerate() {
                for (j, _) in row.iter().enumerate() {
                    if self.blocks.contains(&Crd::from_indices(i, j)) {
                        continue;
                    }

                    for dir in Dir::all() {
                        let v = Crd::from_indices(i, j);

                        for (d, u) in Dir::all()
                            .into_iter()
                            .filter(|d| *d != dir.opposite())
                            .map(|d| (d, v + d.delta()))
                            .filter(|(_, p)| self.in_bounds(*p) && !self.blocks.contains(p))
                        {
                            if let Some(a) = dp[u.ro()][u.co()][d.code()] {
                                if a + self.alt_delta_at(v) >= 0 {
                                    dp_new[i][j][dir.code()] = Some(
                                        dp_new[i][j][dir.code()]
                                            .unwrap_or(i32::MIN)
                                            .max(a + self.alt_delta_at(v)),
                                    );
                                }
                            }
                        }
                    }
                }
            }

            dp = dp_new;
        }

        dp
    }
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

    let world_tile = WorldTile::from(&grid);
    assert_eq!(world_tile.start.ro(), 0);

    let initial_altitude: i32 = 10;
    //let initial_altitude: i32 = 384400;
    let mut start_row: Vec<Vec<Option<i32>>> = vec![vec![None; Dir::all().len()]; world_tile.width];
    start_row[world_tile.start.co()] = vec![Some(initial_altitude); Dir::all().len()];
    //start_row[world_tile.start.co()][Dir::S.code()] = Some(initial_altitude);
    let mut offset: usize = 0;
    let mut result: usize = 0;

    loop {
        let dp = world_tile.max_flight_altitudes(&start_row);

        for (i, row) in dp.iter().enumerate() {
            for cell in row.iter() {
                for dir_cell in cell.iter() {
                    if dir_cell.is_some() {
                        result = result.max(offset + i);
                    }
                }
            }
        }

        start_row = dp.last().unwrap().clone();
        if start_row.iter().all(|xs| xs.iter().all(|x| x.is_none())) {
            break;
        }
        offset += world_tile.height;
    }

    println!("{}", result);
}
