use std::{
    collections::HashSet,
    io::{BufRead, stdin},
};

const FILL_LIMIT: usize = 256;

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

fn crds_of(grid: &[Vec<char>], x: char) -> Vec<Crd> {
    let mut result = vec![];
    for (i, row) in grid.iter().enumerate() {
        for (j, &cell) in row.iter().enumerate() {
            if cell == x {
                result.push(Crd(i as i32, j as i32));
            }
        }
    }
    result
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

fn is_surrounded(sink: Crd, walls: &HashSet<Crd>) -> bool {
    Dir::all().into_iter().all(|dir| {
        let v = sink + dir.delta();
        walls.contains(&v)
    })
}

fn are_all_surrounded(sinks: &[Crd], walls: &HashSet<Crd>) -> bool {
    sinks.iter().all(|&sink| is_surrounded(sink, walls))
}

fn simulate_k_steps_confirm_all_surrounded(source: Crd, sinks: &[Crd], k: usize) -> bool {
    let mut walls: HashSet<Crd> = HashSet::from([source]);
    walls.extend(sinks.iter());

    let mut u: Crd = source;
    let dirs: Vec<_> = Dir::all()
        .into_iter()
        .flat_map(|dir| vec![dir; 3])
        .collect();

    let n = dirs.len();
    let mut dir_index: usize = 0;

    for _ in 0..k {
        while walls.contains(&(u + dirs[dir_index].delta())) {
            dir_index += 1;
            dir_index %= n;
        }

        let v = u + dirs[dir_index].delta();
        walls.insert(v);
        u = v;

        dir_index += 1;
        dir_index %= n;

        for v in dirs.iter().map(|dir| u + dir.delta()) {
            if !walls.contains(&v)
                && let Some(cluster) = bound_flood_fill(&walls, HashSet::from([v]), v)
            {
                walls.extend(cluster);
            }
        }
    }

    are_all_surrounded(sinks, &walls)
}

fn main() {
    let grid: Vec<Vec<char>> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let source = crds_of(&grid, '@')[0];
    let mut sinks: Vec<Crd> = crds_of(&grid, '#');
    let mut sinks_set: HashSet<Crd> = sinks.iter().copied().collect();

    for &sink in &sinks {
        for dir in Dir::all() {
            let v = sink + dir.delta();
            if !sinks_set.contains(&v)
                && let Some(cluster) = bound_flood_fill(&sinks_set, HashSet::from([v]), v)
            {
                sinks_set.extend(cluster);
            }
        }
    }
    sinks = sinks_set.into_iter().collect();

    let mut lo = 0;
    assert!(!simulate_k_steps_confirm_all_surrounded(source, &sinks, lo));
    let mut hi = 10_000;
    assert!(simulate_k_steps_confirm_all_surrounded(source, &sinks, hi));

    while lo + 1 != hi {
        let mid = lo + (hi - lo) / 2;
        if simulate_k_steps_confirm_all_surrounded(source, &sinks, mid) {
            hi = mid;
        } else {
            lo = mid;
        }
    }

    println!("{hi}");
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
