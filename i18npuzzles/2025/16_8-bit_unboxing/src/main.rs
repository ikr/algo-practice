use std::{
    collections::{HashMap, VecDeque},
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

    fn is_empty(self) -> bool {
        self.0 == 0
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
}

fn display_grid(grid: &[Vec<Connectivity>]) {
    for row in grid.iter() {
        let s: String = row.iter().map(|conn| conn.as_char()).collect();
        eprintln!("{}", s);
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
        proto_lines[3..n - 4]
            .iter()
            .map(|line| {
                let cs: Vec<char> = line.chars().collect();
                cs[6..m - 8].iter().collect()
            })
            .collect()
    } else {
        proto_lines
    }
}

fn first_non_empty(grid: &[Vec<Connectivity>]) -> (usize, usize) {
    for (i, row) in grid.iter().enumerate() {
        for (j, cell) in row.iter().enumerate() {
            if !cell.is_empty() {
                return (i, j);
            }
        }
    }
    panic!("Not found")
}

fn adjacent(grid: &[Vec<Connectivity>], i: usize, j: usize) -> Vec<(usize, usize, Dir)> {
    let h = grid.len();
    let w = grid[0].len();
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
        .into_iter()
        .filter(|(r, c, _)| !grid[*r][*c].is_empty())
        .collect()
}

fn connected_to_all_visited(
    grid: &[Vec<Connectivity>],
    visited: &[Vec<bool>],
    i: usize,
    j: usize,
) -> bool {
    adjacent(grid, i, j)
        .into_iter()
        .filter(|(r, c, _)| visited[*r][*c])
        .all(|(ai, aj, dir)| grid[ai][aj].dirs().contains(&dir.opposite()))
}

fn min_rotations(mut grid: Vec<Vec<Connectivity>>) -> usize {
    let (i0, j0) = first_non_empty(&grid);
    let h = grid.len();
    let w = grid[0].len();

    let mut result = 0;
    let mut visited: Vec<Vec<bool>> = vec![vec![false; w]; h];
    visited[i0][j0] = true;
    assert!(connected_to_all_visited(&grid, &visited, i0, j0));
    display_grid(&grid);

    let mut queue: VecDeque<(usize, usize)> = VecDeque::from([(i0, j0)]);
    while let Some((ui, uj)) = queue.pop_front() {
        eprintln!("ui:{} uj:{}", ui, uj);
        while !connected_to_all_visited(&grid, &visited, ui, uj) {
            grid[ui][uj] = grid[ui][uj].rotate();
            result += 1;
        }
        display_grid(&grid);
        for (vi, vj, _) in adjacent(&grid, ui, uj) {
            if !visited[vi][vj] {
                visited[vi][vj] = true;
                queue.push_back((vi, vj));
            }
        }
    }
    result
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

    println!("{}", min_rotations(grid));
}
