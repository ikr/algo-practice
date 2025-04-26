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

    fn as_char(self) -> char {
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

    fn rotations_count(self) -> usize {
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
        let frozen: Vec<Vec<bool>> = vec![vec![false; w]; h];
        Self { grid, frozen }
    }

    fn display_grid(&self) {
        for row in self.grid.iter() {
            let s: String = row.iter().map(|conn| conn.as_char()).collect();
            eprintln!("{}", s);
        }
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

    fn frozen_neighs(&self, i: usize, j: usize) -> Vec<(usize, usize, Dir)> {
        self.adjacent(i, j)
            .into_iter()
            .filter(|(ai, aj, _)| self.frozen[*ai][*aj])
            .collect()
    }

    fn is_direction_wired(&self, i: usize, j: usize, dir: Dir) -> bool {
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

    fn explore(&mut self, i: usize, j: usize, from_dir: Dir) -> Option<usize> {
        self.frozen[i][j] = true;

        let adj = self.adjacent(i, j);
        let adj_dirs: Vec<Dir> = adj.iter().map(|(_, _, d)| *d).collect();
        let fro = self.frozen_neighs(i, j);
        let fro_dirs: Vec<Dir> = fro.iter().map(|(_, _, d)| *d).collect();

        let max_own_rotations = self.grid[i][j].rotations_count();
        let mut own_rotations: usize = 0;

        let all_frozen_are_wired: bool = fro
            .iter()
            .all(|(_, _, d)| self.is_direction_wired(i, j, *d));

        let outbound: Vec<Dir> = self.grid[i][j]
            .dirs()
            .into_iter()
            .filter(|d| *d != from_dir && !fro_dirs.contains(d))
            .collect();

        let all_outbound_are_explorable: bool = outbound.iter().all(|d| adj_dirs.contains(d));

        todo!()
    }

    fn build_pipeline_return_min_rotations(&mut self) -> usize {
        let h = self.grid.len();
        let w = self.grid[0].len();
        self.frozen[h - 1][w - 1] = true;
        self.explore(0, 0, Dir::N).unwrap()
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
    println!("{}", model.build_pipeline_return_min_rotations());
    model.display_grid();
}
