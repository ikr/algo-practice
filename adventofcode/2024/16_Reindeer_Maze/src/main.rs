use std::{
    collections::{BTreeSet, HashMap, HashSet},
    io::{self, BufRead},
};

const TURN_COST: u32 = 1000;
const MOVE_COST: u32 = 1;
const INF: u32 = 100_000_000;

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq, Ord, PartialOrd)]
struct Crd(i16, i16);

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq, Ord, PartialOrd)]
enum Dir {
    N,
    E,
    S,
    W,
}

impl Dir {
    fn delta(&self) -> Crd {
        match self {
            Dir::N => Crd(-1, 0),
            Dir::E => Crd(0, 1),
            Dir::S => Crd(1, 0),
            Dir::W => Crd(0, -1),
        }
    }

    fn turn_left(&self) -> Dir {
        match self {
            Dir::N => Dir::W,
            Dir::E => Dir::N,
            Dir::S => Dir::E,
            Dir::W => Dir::S,
        }
    }

    fn turn_right(&self) -> Dir {
        match self {
            Dir::N => Dir::E,
            Dir::E => Dir::S,
            Dir::S => Dir::W,
            Dir::W => Dir::N,
        }
    }
}

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq, Ord, PartialOrd)]
struct Vert {
    crd: Crd,
    dir: Dir,
}

impl Vert {
    fn new(crd: Crd, dir: Dir) -> Vert {
        Vert { crd, dir }
    }

    fn turn_left(&self) -> Vert {
        Vert {
            crd: self.crd,
            dir: self.dir.turn_left(),
        }
    }

    fn turn_right(&self) -> Vert {
        Vert {
            crd: self.crd,
            dir: self.dir.turn_right(),
        }
    }
}

fn main() {
    let grid: Vec<Vec<char>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let crd_of = |c: char| {
        grid.iter()
            .enumerate()
            .find_map(|(r, row)| {
                row.iter()
                    .position(|&x| x == c)
                    .map(|c| Crd(r as i16, c as i16))
            })
            .unwrap()
    };

    let cell_at = |crd: Crd| grid[crd.0 as usize][crd.1 as usize];

    let adjacent = |u: Vert| -> Vec<(Vert, u32)> {
        let mut vs = vec![(u.turn_left(), TURN_COST), (u.turn_right(), TURN_COST)];
        let new_crd = u.crd + u.dir.delta();
        if cell_at(new_crd) != '#' {
            vs.push((
                Vert {
                    crd: new_crd,
                    dir: u.dir,
                },
                MOVE_COST,
            ));
        }
        vs
    };

    let start = Vert::new(crd_of('S'), Dir::E);
    let end_crd = crd_of('E');
    let ends = [
        Vert::new(end_crd, Dir::N),
        Vert::new(end_crd, Dir::E),
        Vert::new(end_crd, Dir::S),
        Vert::new(end_crd, Dir::W),
    ];

    let mut distances: HashMap<Vert, u32> = HashMap::new();
    distances.insert(start, 0);

    let mut queue: BTreeSet<(u32, Vert)> = BTreeSet::new();
    queue.insert((0, start));

    let mut prev: HashMap<Vert, Vert> = HashMap::new();

    while let Some((wu, u)) = queue.pop_first() {
        queue.remove(&(wu, u));

        for (v, c) in adjacent(u) {
            let wv = *distances.get(&v).unwrap_or(&INF);
            if wu + c < wv {
                queue.remove(&(c, v));
                distances.insert(v, wu + c);
                queue.insert((wu + c, v));
                prev.insert(v, u);
            }
        }
    }

    let result_variants: Vec<u32> = ends
        .iter()
        .map(|v| *distances.get(v).unwrap_or(&INF))
        .collect();
    eprintln!("{:?}", result_variants);

    let optimal_total_cost = result_variants.iter().min().unwrap();
    println!("Optimal total cost: {}", optimal_total_cost);

    let trace_path_from = |v: Vert| -> Vec<Vert> {
        let mut path = vec![v];
        let mut u = v;
        while let Some(&prev_u) = prev.get(&u) {
            path.push(prev_u);
            u = prev_u;
        }
        path.reverse();
        path
    };

    let mut all_optimal_path_crds: HashSet<Crd> = HashSet::new();
    for end in ends
        .iter()
        .filter(|v| *distances.get(v).unwrap() == *optimal_total_cost)
    {
        let path = trace_path_from(*end);
        for v in path.iter() {
            all_optimal_path_crds.insert(v.crd);
        }
    }

    println!(
        "{} tiles are part of at least one of the best paths through the maze",
        all_optimal_path_crds.len()
    );

    eprintln!();
    let mut raster = grid.clone();
    for Crd(i, j) in all_optimal_path_crds.iter() {
        raster[*i as usize][*j as usize] = 'O';
    }
    for row in raster.iter() {
        eprintln!("{}", row.iter().collect::<String>());
    }
}
