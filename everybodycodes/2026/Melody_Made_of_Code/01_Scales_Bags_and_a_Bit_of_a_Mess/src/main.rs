use itertools::Itertools;
use std::io::{BufRead, stdin};

#[derive(Clone, Copy, Debug, PartialEq)]
enum Kind {
    Matte,
    Shiny,
}

impl Kind {
    fn from_shine(x: u8) -> Option<Self> {
        if x <= 30 {
            Some(Self::Matte)
        } else if x >= 33 {
            Some(Self::Shiny)
        } else {
            None
        }
    }
}

#[derive(Clone, Copy, Debug, PartialEq)]
struct Group {
    k: Kind,
    c: char,
}

impl Group {
    fn new(k: Kind, c: char) -> Self {
        Self { k, c }
    }
}

fn decode_component_bits(one_symbol: char, src: &str) -> u8 {
    src.chars()
        .rev()
        .enumerate()
        .map(|(i, x)| if x == one_symbol { 1 << i } else { 0 })
        .sum()
}

struct Tri {
    id: u32,
    r: String,
    g: String,
    b: String,
    s: String,
}

impl Tri {
    fn parse(s: String) -> Self {
        let (a, b) = s.split(':').map(|x| x.to_string()).collect_tuple().unwrap();
        let id: u32 = a.parse().unwrap();
        let (r, g, b, s) = b.split(' ').map(|x| x.to_string()).collect_tuple().unwrap();
        Self { id, r, g, b, s }
    }

    fn shine(&self) -> u8 {
        decode_component_bits('S', &self.s)
    }

    fn dominant_color(&self) -> Option<char> {
        let cs = ['R', 'G', 'B'];

        let xs: Vec<_> = cs
            .iter()
            .zip([&self.r, &self.g, &self.b])
            .map(|(one, s)| decode_component_bits(*one, s))
            .collect();

        let (i0, &hi) = xs.iter().enumerate().max_by_key(|(_, x)| **x).unwrap();
        (xs.iter().filter(|&x| *x == hi).count() == 1).then_some(cs[i0])
    }

    fn group(&self) -> Option<Group> {
        self.dominant_color()
            .and_then(|dc| Kind::from_shine(self.shine()).map(|k| Group::new(k, dc)))
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let tris: Vec<Tri> = lines.into_iter().map(Tri::parse).collect();

    let ts: Vec<_> = tris
        .into_iter()
        .filter_map(|tri| tri.group().map(|g| (g, tri.id)))
        .collect();

    eprintln!("{:?}", ts);

    let cs: Vec<Vec<u32>> = ts
        .into_iter()
        .chunk_by(|&(g, _)| g)
        .into_iter()
        .map(|(_, gids)| gids.into_iter().map(|(_, id)| id).collect::<Vec<_>>())
        .collect();

    eprintln!("{:?}", cs);
}
