use std::{
    collections::HashSet,
    io::{BufRead, stdin},
};

const FILL_LIMIT: usize = 3_000;

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

fn bound_flood_fill(
    walls: &HashSet<Crd>,
    mut covered: HashSet<Crd>,
    u: Crd,
) -> Option<HashSet<Crd>> {
    assert!(covered.contains(&u));

    if covered.len() > FILL_LIMIT {
        return None;
    }

    let adjacent: Vec<Crd> = Dir::all()
        .into_iter()
        .filter_map(|dir| {
            let v = u + dir.delta();
            (!walls.contains(&v) && !covered.contains(&v)).then_some(v)
        })
        .collect();

    for v in adjacent {
        covered.insert(v);

        if let Some(more_covered) = bound_flood_fill(walls, covered, v) {
            covered = more_covered;
        } else {
            return None;
        }
    }

    Some(covered)
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

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_bound_flood_fill_negative() {
        assert_eq!(
            bound_flood_fill(&HashSet::new(), HashSet::from([Crd(0, 0)]), Crd(0, 0)),
            None
        );
    }

    #[test]
    fn test_bound_flood_fill_positive_a() {
        let walls: HashSet<_> = [
            (0, 0),
            (0, 1),
            (0, 2),
            (1, 0),
            (1, 2),
            (2, 0),
            (2, 1),
            (2, 2),
        ]
        .into_iter()
        .map(|(i, j)| Crd(i, j))
        .collect();

        let u = Crd(1, 1);
        let covered = HashSet::from([u]);
        assert_eq!(bound_flood_fill(&walls, covered.clone(), u), Some(covered));
    }

    #[test]
    fn test_bound_flood_fill_positive_b() {
        let walls: HashSet<_> = [
            (0, 0),
            (0, 1),
            (0, 2),
            (0, 3),
            (1, 0),
            (1, 3),
            (2, 0),
            (2, 3),
            (3, 0),
            (3, 3),
            (4, 0),
            (4, 1),
            (4, 2),
            (4, 3),
        ]
        .into_iter()
        .map(|(i, j)| Crd(i, j))
        .collect();

        let u = Crd(1, 1);
        assert_eq!(
            bound_flood_fill(&walls, HashSet::from([u]), u),
            Some(HashSet::from([
                Crd(1, 1),
                Crd(1, 2),
                Crd(2, 1),
                Crd(2, 2),
                Crd(3, 1),
                Crd(3, 2),
            ]))
        );
    }
}
