use std::{
    collections::HashMap,
    io::{BufRead, stdin},
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
    let origin: u8 = 180;
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

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    eprintln!("{:?}", lines);
}
