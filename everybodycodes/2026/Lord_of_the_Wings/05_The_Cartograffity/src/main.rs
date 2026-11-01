use std::{
    collections::HashSet,
    io::{BufRead, stdin},
};

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i32, i32);

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let height = lines.len() as i32;
    let width = lines[0].len() as i32;
    eprintln!("{height} x {width}");
    eprintln!("{lines:?}");

    let dark_cells: HashSet<Crd> = lines
        .into_iter()
        .enumerate()
        .flat_map(|(i, row)| {
            row.bytes()
                .enumerate()
                .filter_map(|(j, x)| (x == b'1').then_some(Crd(i as i32, j as i32)))
                .collect::<Vec<_>>()
        })
        .collect();

    eprintln!("{dark_cells:?}");
}
