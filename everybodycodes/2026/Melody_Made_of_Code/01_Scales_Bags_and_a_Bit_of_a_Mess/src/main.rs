use itertools::Itertools;
use std::{
    cmp::Reverse,
    io::{BufRead, stdin},
};

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

    fn total_coloration(&self) -> u16 {
        ['R', 'G', 'B']
            .into_iter()
            .zip([&self.r, &self.g, &self.b])
            .map(|(one, s)| decode_component_bits(one, s) as u16)
            .sum()
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let tris: Vec<Tri> = lines.into_iter().map(Tri::parse).collect();

    let hi: Tri = tris
        .into_iter()
        .max_by_key(|tri| (tri.shine(), Reverse(tri.total_coloration())))
        .unwrap();

    println!("{}", hi.id);
}
