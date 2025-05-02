use std::{
    collections::HashMap,
    io::{Read, stdin},
};

use itertools::Itertools;
use rand::{random_range, seq::SliceRandom};

const POPULATION_SIZE: usize = 100;
const GENERATIONS_COUNT: usize = 10;
const ALIENS_COUNT: usize = 10;

#[derive(Clone, Copy, Debug, PartialEq)]
enum Dir {
    N,
    E,
    S,
    W,
}

impl Dir {
    fn bit(self) -> u8 {
        match self {
            Dir::N => 1,
            Dir::E => 2,
            Dir::S => 4,
            Dir::W => 8,
        }
    }

    fn all() -> Vec<Dir> {
        vec![Dir::N, Dir::E, Dir::S, Dir::W]
    }

    fn rotate(self) -> Dir {
        match self {
            Dir::N => Dir::E,
            Dir::E => Dir::S,
            Dir::S => Dir::W,
            Dir::W => Dir::N,
        }
    }

    fn opposite(self) -> Dir {
        match self {
            Dir::N => Dir::S,
            Dir::E => Dir::W,
            Dir::S => Dir::N,
            Dir::W => Dir::E,
        }
    }
}

#[derive(Clone, Copy, Debug)]
struct Connectivity(u8);

impl Connectivity {
    fn new(dirs: &[Dir]) -> Self {
        let bits: u8 = dirs.iter().fold(0, |acc, dir| acc | dir.bit());
        Self(bits)
    }

    fn is_empty(self) -> bool {
        self.0 == 0
    }

    fn dirs(self) -> Vec<Dir> {
        Dir::all()
            .iter()
            .filter(|dir| self.0 & dir.bit() != 0)
            .copied()
            .collect()
    }

    fn rotate(self) -> Self {
        Self::new(
            &self
                .dirs()
                .into_iter()
                .map(|d| d.rotate())
                .collect::<Vec<_>>(),
        )
    }

    fn rotate_times(self, k: u8) -> Self {
        (0..k).fold(self, |acc, _| acc.rotate())
    }

    fn symbol(self) -> char {
        match self.0 {
            0 => ' ',
            3 => '└',
            5 => '│',
            6 => '┌',
            7 => '├',
            9 => '┘',
            10 => '─',
            11 => '┴',
            12 => '┐',
            13 => '┤',
            14 => '┬',
            15 => '┼',
            _ => panic!("Connectivity {} is impossible", self.0),
        }
    }

    fn rotations_count(self) -> u8 {
        match self.0 {
            0 | 15 => 0,
            5 | 10 => 1,
            3 | 6 | 7 | 9 | 11 | 12 | 13 | 14 => 3,
            _ => panic!("Connectivity {} is impossible", self.0),
        }
    }
}

#[derive(Clone, Copy, Debug)]
struct Glyph {
    unicode: char,
    connectivity: Connectivity,
}

fn cp_437() -> HashMap<u8, Glyph> {
    let box_glyph_sources_range: Vec<(char, &[Dir])> = vec![
        ('│', &[Dir::N, Dir::S]),
        ('┤', &[Dir::N, Dir::S, Dir::W]),
        ('╡', &[Dir::N, Dir::S, Dir::W]),
        ('╢', &[Dir::N, Dir::S, Dir::W]),
        ('╖', &[Dir::S, Dir::W]),
        ('╕', &[Dir::S, Dir::W]),
        ('╣', &[Dir::N, Dir::S, Dir::W]),
        ('║', &[Dir::N, Dir::S]),
        ('╗', &[Dir::S, Dir::W]),
        ('╝', &[Dir::N, Dir::W]),
        ('╜', &[Dir::N, Dir::W]),
        ('╛', &[Dir::N, Dir::W]),
        ('┐', &[Dir::S, Dir::W]),
        ('└', &[Dir::N, Dir::E]),
        ('┴', &[Dir::N, Dir::E, Dir::W]),
        ('┬', &[Dir::E, Dir::S, Dir::W]),
        ('├', &[Dir::N, Dir::E, Dir::S]),
        ('─', &[Dir::E, Dir::W]),
        ('┼', &[Dir::N, Dir::E, Dir::S, Dir::W]),
        ('╞', &[Dir::N, Dir::E, Dir::S]),
        ('╟', &[Dir::N, Dir::E, Dir::S]),
        ('╚', &[Dir::N, Dir::E]),
        ('╔', &[Dir::E, Dir::S]),
        ('╩', &[Dir::N, Dir::E, Dir::W]),
        ('╦', &[Dir::E, Dir::S, Dir::W]),
        ('╠', &[Dir::N, Dir::E, Dir::S]),
        ('═', &[Dir::E, Dir::W]),
        ('╬', &[Dir::N, Dir::E, Dir::S, Dir::W]),
        ('╧', &[Dir::N, Dir::E, Dir::W]),
        ('╨', &[Dir::N, Dir::E, Dir::W]),
        ('╤', &[Dir::E, Dir::S, Dir::W]),
        ('╥', &[Dir::E, Dir::S, Dir::W]),
        ('╙', &[Dir::N, Dir::E]),
        ('╘', &[Dir::N, Dir::E]),
        ('╒', &[Dir::E, Dir::S]),
        ('╓', &[Dir::E, Dir::S]),
        ('╫', &[Dir::N, Dir::E, Dir::S, Dir::W]),
        ('╪', &[Dir::N, Dir::E, Dir::S, Dir::W]),
        ('┘', &[Dir::N, Dir::W]),
        ('┌', &[Dir::E, Dir::S]),
    ];
    let origin: u8 = 179;
    box_glyph_sources_range
        .into_iter()
        .enumerate()
        .map(|(i, (unicode, dirs))| {
            let connectivity = Connectivity::new(dirs);
            let glyph = Glyph {
                unicode,
                connectivity,
            };
            (origin + i as u8, glyph)
        })
        .collect()
}

fn read_input_bytes() -> Vec<Vec<u8>> {
    let reader = stdin().lock().bytes();
    let mut lines = vec![];
    let mut current_line = vec![];

    for maybe_byte in reader {
        let byte = maybe_byte.unwrap();
        if byte == b'\n' {
            lines.push(current_line);
            current_line = Vec::new();
        } else {
            current_line.push(byte);
        }
    }
    if !current_line.is_empty() {
        lines.push(current_line);
    }
    lines
}

fn remove_decorative_frame(proto_lines: Vec<String>) -> Vec<String> {
    if proto_lines[0].starts_with(' ') {
        let n = proto_lines.len();
        let m = proto_lines[0].chars().count();
        proto_lines[4..n - 5]
            .iter()
            .map(|line| {
                let cs: Vec<char> = line.chars().collect();
                cs[7..m - 8].iter().collect()
            })
            .collect()
    } else {
        proto_lines
            .into_iter()
            .map(|line| line.strip_suffix(' ').unwrap().to_string())
            .collect()
    }
}

#[derive(Clone)]
struct Chromosome(Vec<u8>);

impl Chromosome {
    fn crossover(&self, other: &Chromosome) -> Chromosome {
        let m = random_range(1..self.0.len());
        let mut xs = self.0[0..m].to_vec();
        xs.extend(&other.0[m..]);
        assert_eq!(xs.len(), self.0.len());
        Chromosome(xs)
    }
}

struct Model {
    grid: Vec<Vec<Connectivity>>,
}

impl Model {
    fn display_grid(&self) {
        for row in self.grid.iter() {
            let s: String = row.iter().map(|conn| conn.symbol()).collect();
            eprintln!("{}", s);
        }
        println!();
    }

    fn new_chromosome(&self) -> Chromosome {
        let h = self.grid.len();
        let w = self.grid[0].len();
        let mut xs: Vec<u8> = Vec::with_capacity(h * w);

        for (i, row) in self.grid.iter().enumerate() {
            for (j, cell) in row.iter().enumerate() {
                if !(i == 0 && j == 0) && !(i == h - 1 && j == w - 1) {
                    let n = cell.rotations_count();
                    let x: u8 = if n == 0 { 0 } else { random_range(0..n) };
                    xs.push(x);
                } else {
                    xs.push(0);
                }
            }
        }

        Chromosome(xs)
    }

    fn apply_chromosome(&self, chr: &Chromosome) -> Model {
        let w = self.grid[0].len();
        let mut grid = self.grid.clone();

        for (i, row) in grid.iter_mut().enumerate() {
            for (j, cell) in row.iter_mut().enumerate() {
                let k: u8 = chr.0[i * w + j];
                *cell = cell.rotate_times(k);
            }
        }

        Model { grid }
    }

    fn adjacent(&self, i: usize, j: usize) -> Vec<(usize, usize, Dir)> {
        let h = self.grid.len();
        let w = self.grid[0].len();
        let mut result = vec![];
        if i != 0 {
            result.push((i - 1, j, Dir::N));
        }
        if i < h - 1 {
            result.push((i + 1, j, Dir::S));
        }
        if j != 0 {
            result.push((i, j - 1, Dir::W));
        }
        if j < w - 1 {
            result.push((i, j + 1, Dir::E));
        }
        result
    }

    fn is_direction_wired(&self, i: usize, j: usize, dir: Dir) -> bool {
        if !self.grid[i][j].dirs().contains(&dir) {
            return false;
        }

        let h = self.grid.len();
        let w = self.grid[0].len();

        match dir {
            Dir::N => {
                if i == 0 {
                    j == 0
                } else {
                    self.grid[i - 1][j].dirs().contains(&dir.opposite())
                }
            }
            Dir::E => {
                if j == w - 1 {
                    false
                } else {
                    self.grid[i][j + 1].dirs().contains(&dir.opposite())
                }
            }
            Dir::S => {
                if i == h - 1 {
                    j == w - 1
                } else {
                    self.grid[i + 1][j].dirs().contains(&dir.opposite())
                }
            }
            Dir::W => {
                if j == 0 {
                    false
                } else {
                    self.grid[i][j - 1].dirs().contains(&dir.opposite())
                }
            }
        }
    }

    fn loose_count(&self) -> usize {
        let mut result = 0;
        for (i, row) in self.grid.iter().enumerate() {
            for (j, cell) in row.iter().enumerate() {
                if !cell
                    .dirs()
                    .into_iter()
                    .all(|d| self.is_direction_wired(i, j, d))
                {
                    result += 1;
                }
            }
        }
        result
    }

    fn fitness_rank_with(&self, chr: &Chromosome) -> (usize, usize) {
        let total_rotations: usize = chr.0.iter().map(|&x| x as usize).sum();
        let child = self.apply_chromosome(chr);
        (child.loose_count(), total_rotations)
    }
}

fn main() {
    let bytes = read_input_bytes();
    let glyphs_by_byte = cp_437();
    let translate_row = |xs: &[u8]| -> String {
        xs.iter()
            .map(|x| {
                if let Some(g) = glyphs_by_byte.get(x) {
                    g.unicode
                } else {
                    ' '
                }
            })
            .collect()
    };

    let proto_lines: Vec<String> = bytes.into_iter().map(|xs| translate_row(&xs)).collect();
    let lines = remove_decorative_frame(proto_lines);

    let connectivity_by_char: HashMap<char, Connectivity> = glyphs_by_byte
        .into_values()
        .map(|g| (g.unicode, g.connectivity))
        .collect();

    let grid: Vec<Vec<Connectivity>> = lines
        .into_iter()
        .map(|line| {
            line.chars()
                .map(|c| {
                    if let Some(conn) = connectivity_by_char.get(&c) {
                        *conn
                    } else {
                        Connectivity::new(&[])
                    }
                })
                .collect()
        })
        .collect();

    let model = Model { grid };
    model.display_grid();

    let mut population: Vec<Chromosome> = Vec::with_capacity(POPULATION_SIZE);
    for _ in 0..POPULATION_SIZE {
        population.push(model.new_chromosome());
    }

    let mut rng = rand::rng();

    for _ in 0..GENERATIONS_COUNT {
        let mut next_population: Vec<Chromosome> =
            Vec::with_capacity(POPULATION_SIZE * (POPULATION_SIZE - 1) / 2);

        for (a, b) in population.iter().tuple_combinations() {
            next_population.push(a.crossover(b));
        }

        next_population.select_nth_unstable_by_key(POPULATION_SIZE - ALIENS_COUNT, |chr| {
            model.fitness_rank_with(chr)
        });
        population = next_population[..POPULATION_SIZE - ALIENS_COUNT].to_vec();
        for _ in 0..ALIENS_COUNT {
            population.push(model.new_chromosome());
        }
        population.shuffle(&mut rng);
    }

    let result = model.apply_chromosome(&population[0]);
    result.display_grid();
    eprintln!("{:?}", result.fitness_rank_with(&population[0]));
}
