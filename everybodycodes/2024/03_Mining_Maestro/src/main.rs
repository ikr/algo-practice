use std::{
    collections::HashSet,
    io::{self, BufRead},
};

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i16, i16);

impl Crd {
    fn adjacent(&self) -> Vec<Crd> {
        let Crd(ro, co) = *self;
        vec![
            Crd(ro - 1, co),
            Crd(ro, co + 1),
            Crd(ro + 1, co),
            Crd(ro, co - 1),
        ]
    }
}

fn next_layer(layer: &HashSet<Crd>) -> HashSet<Crd> {
    let mut result = HashSet::new();

    for crd in layer.iter() {
        if crd.adjacent().iter().all(|adj| layer.contains(adj)) {
            result.insert(*crd);
        }
    }

    result
}

fn main() {
    let grid: Vec<Vec<char>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let mut layer: HashSet<Crd> = HashSet::new();

    for (ir, row) in grid.iter().enumerate() {
        for (ic, cell) in row.iter().enumerate() {
            if *cell == '#' {
                layer.insert(Crd(ir as i16, ic as i16));
            }
        }
    }

    let mut result: usize = 0;
    while !layer.is_empty() {
        result += layer.len();
        layer = next_layer(&layer);
    }
    println!("{}", result);
}
