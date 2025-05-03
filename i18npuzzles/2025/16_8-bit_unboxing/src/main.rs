use std::{
    collections::HashMap,
    io::{Read, stdin},
};

use itertools::Itertools;
use rand::random_range;

const POPULATION_SIZE: usize = 300;
const GENERATIONS_COUNT: usize = 20;
const ALIENS_COUNT: usize = 20;

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

    fn alt_symbol(self) -> char {
        match self.0 {
            0 => ' ',
            3 => '╚',
            5 => '║',
            6 => '╔',
            7 => '╠',
            9 => '╝',
            10 => '═',
            11 => '╩',
            12 => '╗',
            13 => '╣',
            14 => '╦',
            15 => '╬',
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
    frozen: Vec<Vec<bool>>,
}

impl Model {
    fn new(grid: Vec<Vec<Connectivity>>) -> Self {
        let h = grid.len();
        let w = grid[0].len();
        assert_ne!(grid[0][0].0, 0);
        assert_ne!(grid[h - 1][w - 1].0, 0);

        let mut frozen: Vec<Vec<bool>> = vec![vec![false; w]; h];
        frozen[0][0] = true;
        frozen[h - 1][w - 1] = true;

        Self { grid, frozen }
    }

    fn display_grid(&self) {
        for (i, row) in self.grid.iter().enumerate() {
            let s: String = row
                .iter()
                .enumerate()
                .map(|(j, conn)| {
                    if self.frozen[i][j] {
                        conn.alt_symbol()
                    } else {
                        conn.symbol()
                    }
                })
                .collect();
            eprintln!("{}", s);
        }
        println!();
    }

    fn apply_apriori_rotations(&mut self, i: usize, j: usize) -> usize {
        let adj = self.adjacent(i, j);

        let empty_dirs: Vec<Dir> = Dir::all()
            .into_iter()
            .filter_map(|d| {
                if let Some((ai, aj, ad)) = adj.iter().find(|(_, _, ad)| *ad == d) {
                    if self.grid[*ai][*aj].is_empty() {
                        Some(*ad)
                    } else {
                        None
                    }
                } else {
                    Some(d)
                }
            })
            .collect();

        let econn = Connectivity::new(&empty_dirs);
        let mut result: usize = 0;

        let rules: Vec<(char, u8, u8)> = vec![
            ('└', 9, 1),
            ('└', 3, 2),
            ('└', 6, 3),
            ('└', 12, 0),
            ('│', 5, 1),
            ('│', 1, 1),
            ('│', 4, 1),
            ('│', 10, 0),
            ('│', 8, 0),
            ('│', 2, 0),
            ('┌', 3, 1),
            ('┌', 6, 2),
            ('┌', 12, 3),
            ('┌', 9, 0),
            ('├', 1, 1),
            ('├', 2, 2),
            ('├', 4, 3),
            ('├', 8, 0),
            ('┘', 9, 2),
            ('┘', 3, 3),
            ('┘', 12, 1),
            ('┘', 6, 0),
            ('─', 10, 1),
            ('─', 8, 1),
            ('─', 2, 1),
            ('─', 5, 0),
            ('─', 1, 0),
            ('─', 4, 0),
            ('┴', 1, 2),
            ('┴', 2, 3),
            ('┴', 8, 1),
            ('┴', 4, 0),
            ('┐', 9, 3),
            ('┐', 6, 1),
            ('┐', 12, 2),
            ('┐', 3, 0),
            ('┤', 1, 3),
            ('┤', 4, 1),
            ('┤', 8, 2),
            ('┤', 2, 0),
            ('┬', 2, 1),
            ('┬', 4, 2),
            ('┬', 8, 3),
            ('┬', 1, 0),
            ('┼', 0, 0),
        ];
        for (c, e, k) in rules {
            if self.grid[i][j].symbol() == c && e == econn.0 {
                self.grid[i][j] = self.grid[i][j].rotate_times(k);
                self.frozen[i][j] = true;
                result += k as usize;
            }
        }

        result
    }

    fn apply_all_apriori_rotations(&mut self) -> usize {
        let h = self.grid.len();
        let w = self.grid[0].len();
        let mut result = 0;

        for i in 0..h {
            for j in 0..w {
                if !(i == 0 && j == 0 || i == h - 1 && j == w - 1) {
                    result += self.apply_apriori_rotations(i, j);
                }
            }
        }

        result
    }

    fn derive_rotations_by_frozen_neighs(&mut self, i: usize, j: usize) -> Option<usize> {
        if self.frozen[i][j] {
            return None;
        }

        let original: Connectivity = self.grid[i][j];
        for k in 0..=original.rotations_count() {
            self.grid[i][j] = self.grid[i][j].rotate_times(k);

            if self.grid[i][j]
                .dirs()
                .iter()
                .all(|&d| self.is_direction_wired(i, j, d) && self.is_direction_frozen(i, j, d))
            {
                self.frozen[i][j] = true;
                return Some(k as usize);
            }
        }
        self.grid[i][j] = original;
        None
    }

    fn derive_all_rotations_by_frozen_neighs(&mut self) -> Option<usize> {
        let h = self.grid.len();
        let w = self.grid[0].len();
        let mut result = 0;
        let mut at_least_one_new = false;

        for i in 0..h {
            for j in 0..w {
                if let Some(k) = self.derive_rotations_by_frozen_neighs(i, j) {
                    result += k;
                    at_least_one_new = true;
                }
            }
        }
        if at_least_one_new { Some(result) } else { None }
    }

    fn apply_manual_rotations(&mut self) -> usize {
        let manual: Vec<(usize, usize, u8)> = vec![
            (1, 2, 1),
            (2, 2, 2),
            (2, 3, 3),
            (2, 4, 2),
            (2, 5, 0),
            (2, 17, 0),
            (2, 18, 0),
            (2, 19, 3),
            (2, 20, 1),
            (2, 22, 1),
            (2, 23, 1),
            (2, 24, 0),
            (2, 25, 0),
            (2, 40, 2),
            (2, 41, 0),
            (3, 41, 2),
            (3, 4, 0),
            (3, 5, 2),
            (3, 10, 1),
            (3, 11, 1),
            (3, 12, 1),
            (3, 13, 3),
            (3, 18, 0),
            (3, 22, 2),
            (4, 22, 1),
            (4, 40, 2),
            (4, 41, 1),
            (4, 42, 1),
            (4, 43, 1),
            (4, 44, 0),
            (5, 2, 1),
            (5, 3, 0),
            (5, 34, 3),
            (5, 33, 1),
            (6, 1, 0),
            (6, 2, 3),
            (6, 3, 0),
            (6, 4, 2),
            (6, 8, 2),
            (6, 12, 0),
            (6, 13, 0),
            (6, 29, 0),
            (7, 1, 0),
            (7, 2, 0),
            (7, 3, 2),
            (7, 4, 1),
            (7, 6, 0),
            (7, 7, 1),
            (7, 8, 1),
            (7, 12, 3),
            (7, 29, 1),
            (7, 64, 2),
            (8, 0, 2),
            (8, 1, 1),
            (8, 2, 1),
            (8, 3, 0),
            (8, 4, 3),
            (8, 5, 0),
            (8, 6, 0),
            (8, 7, 1),
            (8, 8, 1),
            (8, 9, 1),
            (8, 10, 1),
            (8, 11, 1),
            (8, 12, 3),
            (8, 13, 1),
            (8, 29, 0),
            (8, 64, 1),
            (9, 0, 3),
            (9, 1, 3),
            (9, 4, 3),
            (9, 5, 1),
            (9, 6, 0),
            (9, 7, 3),
            (9, 8, 1),
            (9, 9, 0),
            (9, 10, 0),
            (9, 11, 1),
            (9, 12, 2),
            (9, 13, 1),
            (9, 14, 1),
            (9, 63, 2),
            (9, 64, 0),
            (9, 65, 2),
            (10, 9, 3),
            (10, 10, 1),
            (10, 11, 2),
            (10, 12, 1),
            (10, 13, 1),
            (10, 14, 1),
            (10, 63, 0),
            (10, 64, 0),
            (10, 65, 0),
            (11, 1, 1),
            (11, 9, 0),
            (11, 10, 3),
            (11, 38, 1),
            (11, 39, 1),
            (11, 56, 0),
            (11, 57, 1),
            (11, 59, 1),
            (11, 60, 0),
            (11, 61, 0),
            (11, 62, 1),
            (11, 63, 0),
            (11, 64, 1),
            (12, 1, 0),
            (12, 37, 3),
            (12, 38, 3),
            (12, 39, 1),
            (12, 56, 1),
            (12, 61, 3),
            (12, 62, 2),
            (12, 63, 1),
            (12, 64, 0),
            (13, 56, 0),
            (13, 62, 3),
            (13, 63, 1),
            (13, 64, 2),
            (14, 64, 2),
        ];
        for &(i, j, k) in manual.iter() {
            assert!(!self.grid[i][j].is_empty());
            self.grid[i][j] = self.grid[i][j].rotate_times(k);
            self.frozen[i][j] = true;
        }
        manual.iter().map(|(_, _, k)| *k as usize).sum()
    }

    fn chromosome_coordinates(&self) -> Vec<(usize, usize)> {
        let mut result: Vec<(usize, usize)> = vec![];
        for (i, row) in self.grid.iter().enumerate() {
            for (j, cell) in row.iter().enumerate() {
                if !self.frozen[i][j] && cell.rotations_count() != 0 {
                    result.push((i, j));
                }
            }
        }
        result
    }

    fn new_chromosome(&self) -> Chromosome {
        let mut xs: Vec<u8> = vec![];
        for (i, row) in self.grid.iter().enumerate() {
            for (j, cell) in row.iter().enumerate() {
                if !self.frozen[i][j] && cell.rotations_count() != 0 {
                    let x: u8 = random_range(0..cell.rotations_count());
                    xs.push(x);
                }
            }
        }
        Chromosome(xs)
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

    fn is_direction_frozen(&self, i: usize, j: usize, dir: Dir) -> bool {
        let h = self.grid.len();
        let w = self.grid[0].len();

        match dir {
            Dir::N => i == 0 || self.frozen[i - 1][j],
            Dir::E => j == w - 1 || self.frozen[i][j + 1],
            Dir::S => i == h - 1 || self.frozen[i + 1][j],
            Dir::W => j == 0 || self.frozen[i][j - 1],
        }
    }

    fn apply_chromosome(&self, coords: &[(usize, usize)], chr: &Chromosome) -> Model {
        let mut grid = self.grid.clone();

        for (&(i, j), &k) in coords.iter().zip(chr.0.iter()) {
            grid[i][j] = grid[i][j].rotate_times(k);
        }

        Model {
            grid,
            frozen: self.frozen.clone(),
        }
    }

    fn fitness_rank_with(&self, coords: &[(usize, usize)], chr: &Chromosome) -> (usize, usize) {
        let total_rotations: usize = chr.0.iter().map(|&x| x as usize).sum();
        let child = self.apply_chromosome(coords, chr);
        let mut loose_count: usize = 0;

        for &(i, j) in coords.iter() {
            let cell = child.grid[i][j];
            if !cell
                .dirs()
                .into_iter()
                .all(|d| child.is_direction_wired(i, j, d))
            {
                loose_count += 1;
            }
        }

        (loose_count, total_rotations)
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

    let mut model = Model::new(grid);
    model.display_grid();

    let r0 = model.apply_all_apriori_rotations();
    eprintln!("After {} apriori rotations:", r0);
    model.display_grid();

    let mut r1: usize = 0;
    while let Some(k) = model.derive_all_rotations_by_frozen_neighs() {
        r1 += k;
    }
    eprintln!("After {} more derived rotations:", r1);
    model.display_grid();

    let r2 = model.apply_manual_rotations();
    eprintln!("After {} manual rotations:", r2);
    model.display_grid();

    let coords = model.chromosome_coordinates();
    let mut population: Vec<Chromosome> = Vec::with_capacity(POPULATION_SIZE);
    for _ in 0..POPULATION_SIZE {
        population.push(model.new_chromosome());
    }
    eprintln!("Chromosome size: {}", population[0].0.len());

    for _ in 0..GENERATIONS_COUNT {
        let mut next_population: Vec<Chromosome> =
            Vec::with_capacity(POPULATION_SIZE * (POPULATION_SIZE - 1) / 2);

        for (a, b) in population.iter().tuple_combinations() {
            next_population.push(a.crossover(b));
        }

        next_population.select_nth_unstable_by_key(POPULATION_SIZE - ALIENS_COUNT, |chr| {
            model.fitness_rank_with(&coords, chr)
        });
        population = next_population[..POPULATION_SIZE - ALIENS_COUNT].to_vec();
        for _ in 0..ALIENS_COUNT {
            population.push(model.new_chromosome());
        }
        eprint!(".")
    }
    eprintln!();

    let chr0 = &population[0];
    let end_model = model.apply_chromosome(&coords, chr0);
    end_model.display_grid();
    eprintln!("{:?}", end_model.fitness_rank_with(&coords, chr0));

    let result = r0 + r1 + r2 + chr0.0.iter().map(|&k| k as usize).sum::<usize>();
    println!("{}", result);
}
