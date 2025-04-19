use std::{
    collections::HashMap,
    io::{Read, stdin},
};

#[derive(Clone, Copy, Debug)]
enum Dir {
    N,
    E,
    S,
    W,
}

impl Dir {
    fn bit(&self) -> u8 {
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
}

#[derive(Clone, Copy, Debug)]
struct Connectivity(u8);

impl Connectivity {
    fn new(dirs: &[Dir]) -> Self {
        let bits: u8 = dirs.iter().fold(0, |acc, dir| acc | dir.bit());
        Self(bits)
    }

    fn dirs(&self) -> Vec<Dir> {
        Dir::all()
            .iter()
            .filter(|dir| self.0 & dir.bit() != 0)
            .copied()
            .collect()
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
    if proto_lines[0].chars().next().unwrap() == ' ' {
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
    for line in proto_lines.iter() {
        eprintln!("{}", line);
    }
    eprintln!("---------------");

    let lines = remove_decorative_frame(proto_lines);
    for line in lines {
        eprintln!("{}", line);
    }
}
