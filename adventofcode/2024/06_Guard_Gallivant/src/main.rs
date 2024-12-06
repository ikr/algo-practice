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

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
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

    fn turn_right(&self) -> Dir {
        match self {
            Dir::N => Dir::E,
            Dir::E => Dir::S,
            Dir::S => Dir::W,
            Dir::W => Dir::N,
        }
    }
}

fn guard_position(grid: &[Vec<char>]) -> Crd {
    for (i, row) in grid.iter().enumerate() {
        for (j, &cell) in row.iter().enumerate() {
            if cell == '^' {
                return Crd(i as i32, j as i32);
            }
        }
    }
    panic!("^ not found");
}

fn is_looped(grid: &[Vec<char>], initial_pos: Crd) -> bool {
    let h = grid.len() as i32;
    let w = grid[0].len() as i32;

    let in_bounds = |Crd(ro, co): Crd| 0 <= ro && ro < h && 0 <= co && co < w;
    let cell_at = |Crd(ro, co): Crd| grid[ro as usize][co as usize];

    let mut pos = initial_pos;
    let mut dir = Dir::N;

    let mut states: HashSet<(Crd, Dir)> = HashSet::new();
    states.insert((pos, dir));

    loop {
        let next_pos = pos + dir.delta();
        if !in_bounds(next_pos) {
            return false;
        }

        if cell_at(next_pos) == '#' {
            dir = dir.turn_right();
        } else {
            pos = next_pos;
        }
        if states.contains(&(pos, dir)) {
            return true;
        }
        states.insert((pos, dir));
    }
}

fn main() {
    let mut grid: Vec<Vec<char>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let initial_pos = guard_position(&grid);
    let mut result = 0;
    for i in 0..(grid.len()) {
        for j in 0..(grid[i].len()) {
            if grid[i][j] == '.' && Crd(i as i32, j as i32) != initial_pos {
                grid[i][j] = '#';
                if is_looped(&grid, initial_pos) {
                    result += 1;
                }
                grid[i][j] = '.';
            }
        }
    }
    println!("{}", result);
}
