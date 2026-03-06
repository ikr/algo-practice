use std::{
    collections::HashSet,
    io::{BufRead, stdin},
};

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i32, i32);

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
    fn all() -> Vec<Self> {
        vec![Self::N, Self::E, Self::S, Self::W]
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

fn crd_of(grid: &[Vec<char>], x: char) -> Option<Crd> {
    for (i, row) in grid.iter().enumerate() {
        for (j, &cell) in row.iter().enumerate() {
            if cell == x {
                return Some(Crd(i as i32, j as i32));
            }
        }
    }
    None
}

fn main() {
    let grid: Vec<Vec<char>> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let source = crd_of(&grid, '@').unwrap();
    let sink = crd_of(&grid, '#').unwrap();
    let mut coverage: HashSet<Crd> = HashSet::from([source]);
    let mut u: Crd = source;
    let dirs = Dir::all();
    let n = dirs.len();
    let mut dir_index: usize = 0;

    while u != sink {
        while coverage.contains(&(u + dirs[dir_index].delta())) {
            dir_index += 1;
            dir_index %= n;
        }

        let v = u + dirs[dir_index].delta();
        coverage.insert(v);
        u = v;

        dir_index += 1;
        dir_index %= n;
    }

    println!("{}", coverage.len() - 1);
}
