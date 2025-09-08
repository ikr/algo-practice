use std::io::{BufRead, stdin};

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

    fn neighs(self, grid: &[Vec<i8>]) -> Vec<Self> {
        let h = grid.len();
        let w = grid[0].len();
        let Self(i, j) = self;
        let mut result = vec![];

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
}

impl Exploration {
    fn new(grid: Vec<Vec<i8>>, rolls: Vec<i8>) -> Self {
        let h = grid.len();
        let w = grid[0].len();
        let visited = vec![vec![false; w]; h];

        Self {
            grid,
            rolls,
            visited,
        }
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

    let mut dies: Vec<Die> = lines[..isep]
        .iter()
        .map(|line| Die::new(extract_faces(line), extract_seed(line)))
        .collect();

    let grid: Vec<Vec<i8>> = lines[isep + 1..]
        .iter()
        .map(|s| s.bytes().map(|x| (x - b'0') as i8).collect())
        .collect();

    eprintln!("{:?}", grid);
    eprintln!("{} x {}", grid.len(), grid[0].len());
    eprintln!("{:?}", k_rolls(32, dies.pop().unwrap()));
}
