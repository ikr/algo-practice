use std::{
    collections::HashSet,
    io::{BufRead, stdin},
};

struct Die {
    faces: Vec<i8>,
    seed: usize,
    pulse: usize,
    current_face_index: usize,
    roll_number: usize,
}

impl Die {
    fn new(faces: Vec<i8>, seed: usize) -> Self {
        Self {
            faces,
            seed,
            pulse: seed,
            current_face_index: 0,
            roll_number: 0,
        }
    }

    fn value(&self) -> i8 {
        self.faces[self.current_face_index]
    }

    fn roll(&mut self) {
        self.roll_number += 1;
        let spin = self.roll_number * self.pulse;

        self.current_face_index += spin;
        self.current_face_index %= self.faces.len();

        self.pulse += spin;
        self.pulse %= self.seed;
        self.pulse = self.pulse + 1 + self.roll_number + self.seed;
    }
}

#[derive(Clone, Copy, Debug)]
struct Crd(usize, usize);

impl Crd {
    fn get(self, grid: &[Vec<i8>]) -> i8 {
        grid[self.0][self.1]
    }

    fn neighs(self, h: usize, w: usize) -> Vec<Self> {
        let Self(i, j) = self;
        let mut result = vec![self];

        if i != 0 {
            result.push(Self(i - 1, j));
        }
        if j != w - 1 {
            result.push(Self(i, j + 1));
        }
        if i != h - 1 {
            result.push(Self(i + 1, j));
        }
        if j != 0 {
            result.push(Self(i, j - 1));
        }

        result
    }
}

struct Exploration {
    grid: Vec<Vec<i8>>,
    rolls: Vec<i8>,
    visited: Vec<Vec<bool>>,
    states: HashSet<(usize, usize, usize)>,
}

impl Exploration {
    fn new(grid: Vec<Vec<i8>>) -> Self {
        let h = grid.len();
        let w = grid[0].len();
        let visited = vec![vec![false; w]; h];

        Self {
            grid,
            rolls: vec![],
            visited,
            states: HashSet::new(),
        }
    }

    fn set_rolls(&mut self, rolls: Vec<i8>) {
        self.rolls = rolls;
        self.states = HashSet::new();
    }

    fn recur(&mut self, mut path: Vec<Crd>, iroll: usize) {
        let p = path.last().unwrap();
        self.states.insert((p.0, p.1, iroll));

        assert_eq!(p.get(&self.grid), self.rolls[iroll]);
        assert!(iroll + 1 < self.rolls.len());
        let h = self.grid.len();
        let w = self.grid[0].len();

        let qs: Vec<_> = p
            .neighs(h, w)
            .into_iter()
            .filter(|q| {
                q.get(&self.grid) == self.rolls[iroll + 1]
                    && !self.states.contains(&(q.0, q.1, iroll + 1))
            })
            .collect();

        if qs.is_empty() {
            for Crd(i, j) in path {
                self.visited[i][j] = true;
            }
        } else {
            for q in qs {
                path.push(q);
                self.recur(path.clone(), iroll + 1);
                path.pop();
            }
        }
    }

    fn start_at(&mut self, crd: Crd) {
        if crd.get(&self.grid) == self.rolls[0] {
            self.recur(vec![crd], 0);
        }
    }

    fn total_visited(&self) -> usize {
        self.visited
            .iter()
            .map(|row| row.iter().filter(|x| **x).count())
            .sum()
    }
}

fn extract_faces(input_line: &str) -> Vec<i8> {
    let csv = input_line.split(['[', ']']).nth(1).unwrap();
    csv.split(',').map(|s| s.parse().unwrap()).collect()
}

fn extract_seed(input_line: &str) -> usize {
    input_line.split('=').next_back().unwrap().parse().unwrap()
}

fn k_rolls(k: usize, d0: Die) -> Vec<i8> {
    (0..k)
        .scan(d0, |d, _| {
            d.roll();
            Some(d.value())
        })
        .collect()
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let isep = lines.iter().position(|s| s.is_empty()).unwrap();

    let dies: Vec<Die> = lines[..isep]
        .iter()
        .map(|line| Die::new(extract_faces(line), extract_seed(line)))
        .collect();

    let grid: Vec<Vec<i8>> = lines[isep + 1..]
        .iter()
        .map(|s| s.bytes().map(|x| (x - b'0') as i8).collect())
        .collect();

    let h = grid.len();
    let w = grid[0].len();
    let mut expl = Exploration::new(grid);

    for d in dies {
        let rolls = k_rolls(5_000, d);
        expl.set_rolls(rolls);

        for i in 0..h {
            for j in 0..w {
                expl.start_at(Crd(i, j));
            }
        }
    }
    println!("{}", expl.total_visited());
}
