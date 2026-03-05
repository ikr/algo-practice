use itertools::Itertools;
use std::io::{BufRead, stdin};

fn decode_component_bits(one_symbol: char, src: &str) -> u8 {
    src.chars()
        .rev()
        .enumerate()
        .map(|(i, x)| if x == one_symbol { 1 << i } else { 0 })
        .sum()
}

struct Tri {
    id: u16,
    r: String,
    g: String,
    b: String,
}

impl Tri {
    fn parse(s: String) -> Self {
        let (a, b) = s.split(':').map(|x| x.to_string()).collect_tuple().unwrap();
        let id: u16 = a.parse().unwrap();
        let (r, g, b) = b.split(' ').map(|x| x.to_string()).collect_tuple().unwrap();
        Self { id, r, g, b }
    }

    fn is_green_dominant(&self) -> bool {
        let (br, bg, bb) = ['R', 'G', 'B']
            .into_iter()
            .zip([&self.r, &self.g, &self.b])
            .map(|(one, s)| decode_component_bits(one, s))
            .collect_tuple()
            .unwrap();

        bg > br && bg > bb
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let tris: Vec<Tri> = lines.into_iter().map(Tri::parse).collect();

    let gg: Vec<_> = tris
        .into_iter()
        .filter(|tri| tri.is_green_dominant())
        .collect();

    let result: u32 = gg.into_iter().map(|tri| tri.id as u32).sum();
    println!("{result}");
}
