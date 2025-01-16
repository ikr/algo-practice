use std::{
    collections::{HashSet, VecDeque},
    io::BufRead,
};

const FLOOD_LIMIT: usize = 100_000;

#[derive(Clone, Copy, Debug, Hash, PartialEq, Eq)]
struct Crd(i32, i32);

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;
    fn add(self, other: Crd) -> Crd {
        Crd(self.0 + other.0, self.1 + other.1)
    }
}

#[derive(Clone, Copy, Debug, PartialEq)]
enum Dir {
    U,
    R,
    D,
    L,
}

impl Dir {
    fn from(s: &str) -> Dir {
        match s {
            "U" => Dir::U,
            "R" => Dir::R,
            "D" => Dir::D,
            "L" => Dir::L,
            _ => panic!("Invalid direction literal `{}`", s),
        }
    }

    fn delta(&self) -> Crd {
        match self {
            Dir::U => Crd(-1, 0),
            Dir::R => Crd(0, 1),
            Dir::D => Crd(1, 0),
            Dir::L => Crd(0, -1),
        }
    }

    fn all() -> Vec<Dir> {
        vec![Dir::U, Dir::R, Dir::D, Dir::L]
    }
}

fn parse_line(s: &str) -> (Dir, usize) {
    let parts = s.split_whitespace().collect::<Vec<_>>();
    (Dir::from(parts[0]), parts[1].parse().unwrap())
}

fn limited_flood_fill_size(path: &[Crd], source: Crd) -> Option<usize> {
    let mut visited: HashSet<Crd> = path.iter().copied().collect();
    visited.insert(source);
    let mut q: VecDeque<Crd> = VecDeque::from([source]);

    while let Some(u) = q.pop_front() {
        for dir in Dir::all() {
            let v = u + dir.delta();
            if !visited.contains(&v) {
                visited.insert(v);
                if visited.len() > FLOOD_LIMIT {
                    return None;
                }
                q.push_back(v);
            }
        }
    }

    Some(visited.len())
}

fn main() {
    let lines: Vec<String> = std::io::stdin()
        .lock()
        .lines()
        .map(|a| a.unwrap().to_string())
        .collect();

    let instructions = lines
        .into_iter()
        .map(|s| parse_line(&s))
        .collect::<Vec<_>>();

    let deltas: Vec<Dir> = instructions
        .into_iter()
        .flat_map(|(dir, steps)| vec![dir; steps])
        .collect::<Vec<_>>();

    let path: Vec<Crd> = deltas.into_iter().fold(vec![], |mut acc, dir| {
        if let Some(&last) = acc.last() {
            acc.push(last + dir.delta());
        } else {
            acc.push(Crd(0, 0));
            acc.push(dir.delta());
        }
        acc
    });

    let result: usize = [
        Dir::L.delta() + Dir::U.delta(),
        Dir::U.delta() + Dir::R.delta(),
        Dir::R.delta() + Dir::D.delta(),
        Dir::D.delta() + Dir::L.delta(),
    ]
    .into_iter()
    .filter_map(|source| limited_flood_fill_size(&path, source))
    .next()
    .unwrap();

    println!("{}", result);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn parse_line_works() {
        assert_eq!(parse_line("R 10 (#508fe2)"), (Dir::R, 10));
    }
}
