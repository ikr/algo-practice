use std::{
    collections::HashMap,
    io::{Read, stdin},
};

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
}

#[derive(Clone, Copy, Debug)]
struct BiConnectivity(Connectivity, Connectivity);

impl BiConnectivity {
    fn is_empty(self) -> bool {
        self.0.is_empty() && self.1.is_empty()
    }

    fn rotations_count(self) -> u8 {
        match (self.0.0, self.1.0) {
            (0, 0) | (0, 15) | (15, 0) => 0,
            (0, 5) | (5, 0) | (0, 10) | (10, 0) => 1,
            _ => 3,
        }
    }

    fn rotate_times(self, k: u8) -> Self {
        Self(self.0.rotate_times(k), self.1.rotate_times(k))
    }
}

#[derive(Clone, Copy, Debug)]
struct Glyph {
    unicode: char,
    biconnectivity: BiConnectivity,
}

fn box_glyph_sources_range() -> Vec<(char, Vec<Dir>, Vec<Dir>)> {
    vec![
        ('│', vec![Dir::N, Dir::S], vec![]),
        ('┤', vec![Dir::N, Dir::S, Dir::W], vec![]),
        ('╡', vec![Dir::N, Dir::S], vec![Dir::W]),
        ('╢', vec![Dir::W], vec![Dir::N, Dir::S]),
        ('╖', vec![Dir::W], vec![Dir::S]),
        ('╕', vec![Dir::S], vec![Dir::W]),
        ('╣', vec![], vec![Dir::N, Dir::S, Dir::W]),
        ('║', vec![], vec![Dir::N, Dir::S]),
        ('╗', vec![], vec![Dir::S, Dir::W]),
        ('╝', vec![], vec![Dir::N, Dir::W]),
        ('╜', vec![Dir::W], vec![Dir::N]),
        ('╛', vec![Dir::N], vec![Dir::W]),
        ('┐', vec![Dir::S, Dir::W], vec![]),
        ('└', vec![Dir::N, Dir::E], vec![]),
        ('┴', vec![Dir::N, Dir::E, Dir::W], vec![]),
        ('┬', vec![Dir::E, Dir::S, Dir::W], vec![]),
        ('├', vec![Dir::N, Dir::E, Dir::S], vec![]),
        ('─', vec![Dir::E, Dir::W], vec![]),
        ('┼', vec![Dir::N, Dir::E, Dir::S, Dir::W], vec![]),
        ('╞', vec![Dir::N, Dir::S], vec![Dir::E]),
        ('╟', vec![Dir::E], vec![Dir::N, Dir::S]),
        ('╚', vec![], vec![Dir::N, Dir::E]),
        ('╔', vec![], vec![Dir::E, Dir::S]),
        ('╩', vec![], vec![Dir::N, Dir::E, Dir::W]),
        ('╦', vec![], vec![Dir::E, Dir::S, Dir::W]),
        ('╠', vec![], vec![Dir::N, Dir::E, Dir::S]),
        ('═', vec![], vec![Dir::E, Dir::W]),
        ('╬', vec![], vec![Dir::N, Dir::E, Dir::S, Dir::W]),
        ('╧', vec![Dir::N], vec![Dir::E, Dir::W]),
        ('╨', vec![Dir::E, Dir::W], vec![Dir::N]),
        ('╤', vec![Dir::S], vec![Dir::E, Dir::W]),
        ('╥', vec![Dir::E, Dir::W], vec![Dir::S]),
        ('╙', vec![Dir::E], vec![Dir::N]),
        ('╘', vec![Dir::N], vec![Dir::E]),
        ('╒', vec![Dir::S], vec![Dir::E]),
        ('╓', vec![Dir::E], vec![Dir::S]),
        ('╫', vec![Dir::E, Dir::W], vec![Dir::N, Dir::S]),
        ('╪', vec![Dir::N, Dir::S], vec![Dir::E, Dir::W]),
        ('┘', vec![Dir::N, Dir::W], vec![]),
        ('┌', vec![Dir::E, Dir::S], vec![]),
    ]
}

fn symbol(biconnectivity: BiConnectivity) -> char {
    box_glyph_sources_range()
        .iter()
        .find(|(_, dirs1, dirs2)| {
            let bits1 = Connectivity::new(dirs1).0;
            let bits2 = Connectivity::new(dirs2).0;
            biconnectivity.0.0 == bits1 && biconnectivity.1.0 == bits2
        })
        .unwrap()
        .0
}

fn cp_437() -> HashMap<u8, Glyph> {
    let origin: u8 = 179;
    box_glyph_sources_range()
        .into_iter()
        .enumerate()
        .map(|(i, (unicode, dirs1, dirs2))| {
            let connectivity1 = Connectivity::new(&dirs1);
            let connectivity2 = Connectivity::new(&dirs2);
            let biconnectivity = BiConnectivity(connectivity1, connectivity2);
            let glyph = Glyph {
                unicode,
                biconnectivity,
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

struct Model {
    grid: Vec<Vec<BiConnectivity>>,
    frozen: Vec<Vec<bool>>,
}

impl Model {
    fn new(grid: Vec<Vec<BiConnectivity>>) -> Self {
        let h = grid.len();
        let w = grid[0].len();
        assert!(!grid[0][0].is_empty());
        assert!(!grid[h - 1][w - 1].is_empty());

        let mut frozen: Vec<Vec<bool>> = vec![vec![false; w]; h];
        frozen[0][0] = true;
        frozen[h - 1][w - 1] = true;

        Self { grid, frozen }
    }

    fn display_grid(&self) {
        for row in self.grid.iter() {
            let s: String = row.iter().map(|biconn| symbol(*biconn)).collect();
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
            if self.grid[i][j].symbol() == c && e == econn.0 && !self.frozen[i][j] {
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
                && !self.frozen[i][j]
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
            (1, 26, 0),
            (1, 27, 3),
            (1, 55, 2),
            (1, 56, 1),
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
            (2, 26, 3),
            (2, 27, 3),
            (2, 28, 0),
            (2, 29, 2),
            (2, 30, 1),
            (2, 31, 3),
            (2, 40, 2),
            (2, 41, 0),
            (2, 53, 3),
            (2, 54, 1),
            (2, 55, 2),
            (2, 56, 1),
            (3, 4, 0),
            (3, 5, 2),
            (3, 10, 1),
            (3, 11, 1),
            (3, 12, 1),
            (3, 13, 3),
            (3, 18, 0),
            (3, 19, 1),
            (3, 20, 2),
            (3, 22, 2),
            (3, 26, 0),
            (3, 27, 0),
            (3, 28, 0),
            (3, 29, 0),
            (3, 30, 3),
            (3, 31, 0),
            (3, 41, 2),
            (3, 49, 3),
            (3, 50, 3),
            (3, 51, 0),
            (3, 52, 1),
            (3, 53, 1),
            (3, 54, 1),
            (3, 55, 0),
            (3, 56, 2),
            (4, 17, 2),
            (4, 18, 1),
            (4, 19, 1),
            (4, 20, 0),
            (4, 22, 1),
            (4, 27, 1),
            (4, 28, 1),
            (4, 29, 2),
            (4, 30, 1),
            (4, 40, 2),
            (4, 41, 1),
            (4, 42, 1),
            (4, 43, 1),
            (4, 44, 0),
            (4, 48, 3),
            (4, 49, 0),
            (4, 50, 1),
            (4, 51, 0),
            (4, 52, 1),
            (4, 53, 0),
            (4, 54, 1),
            (4, 55, 0),
            (4, 56, 1),
            (5, 2, 1),
            (5, 3, 0),
            (5, 17, 0),
            (5, 18, 1),
            (5, 19, 0),
            (5, 20, 1),
            (5, 21, 0),
            (5, 22, 0),
            (5, 26, 2),
            (5, 27, 1),
            (5, 28, 0),
            (5, 29, 3),
            (5, 30, 2),
            (5, 34, 3),
            (5, 33, 1),
            (5, 44, 2),
            (5, 45, 3),
            (5, 49, 0),
            (5, 46, 3),
            (5, 50, 1),
            (5, 51, 1),
            (5, 52, 1),
            (5, 53, 0),
            (5, 54, 2),
            (5, 55, 0),
            (5, 56, 1),
            (6, 1, 0),
            (6, 2, 3),
            (6, 3, 0),
            (6, 4, 2),
            (6, 8, 2),
            (6, 12, 0),
            (6, 13, 0),
            (6, 14, 0),
            (6, 15, 1),
            (6, 16, 1),
            (6, 17, 1),
            (6, 18, 2),
            (6, 19, 0),
            (6, 20, 3),
            (6, 21, 3),
            (6, 22, 1),
            (6, 23, 0),
            (6, 26, 3),
            (6, 27, 0),
            (6, 28, 1),
            (6, 29, 0),
            (6, 44, 3),
            (6, 45, 2),
            (6, 53, 3),
            (6, 54, 3),
            (6, 55, 0),
            (6, 56, 0),
            (7, 1, 0),
            (7, 2, 0),
            (7, 3, 2),
            (7, 4, 1),
            (7, 6, 0),
            (7, 7, 1),
            (7, 8, 1),
            (7, 12, 3),
            (7, 14, 1),
            (7, 15, 0),
            (7, 16, 2),
            (7, 17, 1),
            (7, 18, 3),
            (7, 19, 1),
            (7, 20, 1),
            (7, 21, 3),
            (7, 22, 1),
            (7, 23, 2),
            (7, 26, 2),
            (7, 27, 2),
            (7, 28, 1),
            (7, 29, 1),
            (7, 44, 2),
            (7, 45, 2),
            (7, 46, 2),
            (7, 53, 0),
            (7, 54, 3),
            (7, 55, 1),
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
            (8, 14, 1),
            (8, 15, 2),
            (8, 16, 2),
            (8, 17, 2),
            (8, 18, 1),
            (8, 19, 3),
            (8, 20, 3),
            (8, 21, 1),
            (8, 22, 1),
            (8, 23, 1),
            (8, 24, 0),
            (8, 28, 2),
            (8, 29, 0),
            (8, 42, 0),
            (8, 43, 1),
            (8, 44, 1),
            (8, 45, 0),
            (8, 46, 1),
            (8, 52, 3),
            (8, 53, 3),
            (8, 54, 1),
            (8, 55, 1),
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
            (9, 15, 0),
            (9, 16, 1),
            (9, 17, 1),
            (9, 21, 1),
            (9, 22, 2),
            (9, 23, 0),
            (9, 24, 1),
            (9, 43, 0),
            (9, 44, 3),
            (9, 45, 1),
            (9, 46, 1),
            (9, 47, 1),
            (9, 48, 1),
            (9, 49, 1),
            (9, 50, 1),
            (9, 55, 3),
            (9, 63, 2),
            (9, 64, 0),
            (9, 65, 2),
            (10, 9, 3),
            (10, 10, 1),
            (10, 11, 2),
            (10, 12, 1),
            (10, 13, 1),
            (10, 14, 1),
            (10, 15, 0),
            (10, 16, 2),
            (10, 17, 1),
            (10, 20, 1),
            (10, 21, 1),
            (10, 22, 1),
            (10, 23, 0),
            (10, 24, 0),
            (10, 43, 0),
            (10, 44, 3),
            (10, 47, 0),
            (10, 48, 2),
            (10, 49, 1),
            (10, 50, 1),
            (10, 51, 3),
            (10, 55, 0),
            (10, 63, 0),
            (10, 64, 0),
            (10, 65, 0),
            (11, 1, 1),
            (11, 9, 0),
            (11, 10, 3),
            (11, 11, 2),
            (11, 12, 1),
            (11, 13, 0),
            (11, 14, 2),
            (11, 15, 1),
            (11, 16, 1),
            (11, 17, 3),
            (11, 18, 0),
            (11, 19, 3),
            (11, 20, 2),
            (11, 21, 1),
            (11, 22, 0),
            (11, 23, 3),
            (11, 24, 1),
            (11, 38, 1),
            (11, 39, 1),
            (11, 40, 0),
            (11, 41, 2),
            (11, 42, 1),
            (11, 43, 2),
            (11, 44, 0),
            (11, 48, 0),
            (11, 49, 0),
            (11, 50, 0),
            (11, 51, 1),
            (11, 56, 0),
            (11, 57, 1),
            (11, 59, 1),
            (11, 60, 0),
            (11, 61, 0),
            (11, 62, 1),
            (11, 63, 0),
            (11, 64, 1),
            (12, 1, 0),
            (12, 11, 2),
            (12, 12, 3),
            (12, 13, 0),
            (12, 14, 1),
            (12, 15, 1),
            (12, 16, 1),
            (12, 17, 0),
            (12, 18, 0),
            (12, 19, 1),
            (12, 20, 1),
            (12, 21, 0),
            (12, 22, 3),
            (12, 23, 0),
            (12, 37, 3),
            (12, 38, 3),
            (12, 39, 1),
            (12, 40, 2),
            (12, 41, 1),
            (12, 42, 3),
            (12, 43, 3),
            (12, 44, 1),
            (12, 45, 2),
            (12, 46, 3),
            (12, 47, 2),
            (12, 48, 1),
            (12, 52, 3),
            (12, 56, 1),
            (12, 61, 3),
            (12, 62, 2),
            (12, 63, 1),
            (12, 64, 0),
            (13, 11, 0),
            (13, 12, 1),
            (13, 13, 1),
            (13, 14, 1),
            (13, 15, 1),
            (13, 16, 0),
            (13, 17, 3),
            (13, 18, 0),
            (13, 19, 1),
            (13, 20, 3),
            (13, 21, 3),
            (13, 22, 1),
            (13, 23, 1),
            (13, 40, 2),
            (13, 41, 0),
            (13, 42, 1),
            (13, 43, 1),
            (13, 44, 1),
            (13, 45, 3),
            (13, 46, 2),
            (13, 47, 0),
            (13, 48, 1),
            (13, 52, 0),
            (13, 56, 0),
            (13, 62, 3),
            (13, 63, 1),
            (13, 64, 2),
            (14, 16, 2),
            (14, 17, 3),
            (14, 18, 1),
            (14, 19, 1),
            (14, 22, 2),
            (14, 23, 2),
            (14, 42, 2),
            (14, 43, 1),
            (14, 47, 0),
            (14, 48, 0),
            (14, 64, 2),
        ];
        for &(i, j, k) in manual.iter() {
            if self.frozen[i][j] {
                continue;
            }

            assert!(!self.grid[i][j].is_empty());
            let conn: Connectivity = self.grid[i][j];
            if k > 1 {
                assert!(![5, 10].contains(&conn.0));
            }
            assert_ne!(15, conn.0);

            self.grid[i][j] = self.grid[i][j].rotate_times(k);
            self.frozen[i][j] = true;
        }
        manual.iter().map(|(_, _, k)| *k as usize).sum()
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

    let result = r0 + r1 + r2;
    println!("{}", result);
}
