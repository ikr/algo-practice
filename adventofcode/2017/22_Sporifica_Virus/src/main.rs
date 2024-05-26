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

#[derive(Debug, Clone, Copy)]
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

    fn turn_around(&self) -> Dir {
        match self {
            Dir::N => Dir::S,
            Dir::E => Dir::W,
            Dir::S => Dir::N,
            Dir::W => Dir::E,
        }
    }
}

fn infected_nodes(grid: &[Vec<char>]) -> HashSet<Crd> {
    let h = grid.len() as i32;
    let w = grid[0].len() as i32;
    let mut result = HashSet::new();

    for (i, row) in grid.iter().enumerate() {
        for (j, x) in row.iter().enumerate() {
            if *x == '#' {
                result.insert(Crd(i as i32 - h / 2, j as i32 - w / 2));
            }
        }
    }

    result
}

fn main() {
    let grid: Vec<Vec<char>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let mut weakened: HashSet<Crd> = HashSet::new();
    let mut infected = infected_nodes(&grid);
    let mut flagged: HashSet<Crd> = HashSet::new();

    let mut crd = Crd(0, 0);
    let mut dir = Dir::N;
    let mut result = 0;

    for _ in 0..10000000 {
        if infected.contains(&crd) {
            dir = dir.turn_right();
            infected.remove(&crd);
            flagged.insert(crd);
        } else if weakened.contains(&crd) {
            weakened.remove(&crd);
            infected.insert(crd);
            result += 1;
        } else if flagged.contains(&crd) {
            dir = dir.turn_around();
            flagged.remove(&crd);
        } else {
            // The node is clean
            dir = dir.turn_left();
            weakened.insert(crd);
        }

        crd = crd + dir.delta();
    }

    println!("{}", result);
}
