use std::{
    collections::{BTreeSet, HashMap},
    io::{self, BufRead},
};

const INF: u16 = 30000;

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(usize, usize);

fn levels_diff(x: u16, y: u16) -> u16 {
    let mut xs = [x, y];
    xs.sort();
    (xs[1] - xs[0]).min(10 - xs[1] + xs[0])
}

fn main() {
    let grid: Vec<Vec<char>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let level_at = |crd: Crd| -> u16 {
        let x = grid[crd.0][crd.1];
        match x {
            '#' | ' ' => panic!("Why would you want a level of a `{}` at {:?}?", x, crd),
            'S' | 'E' => 0,
            _ => x.to_digit(10).unwrap() as u16,
        }
    };

    let cell_at = |crd: Crd| -> char { grid[crd.0][crd.1] };

    let is_walkable = |crd: Crd| -> bool {
        let x = cell_at(crd);
        x != '#' && x != ' '
    };

    let adjacent_of = |crd: Crd| -> Vec<Crd> {
        let mut result = vec![];
        if crd.0 != 0 && is_walkable(Crd(crd.0 - 1, crd.1)) {
            result.push(Crd(crd.0 - 1, crd.1));
        }
        if crd.1 != 0 && is_walkable(Crd(crd.0, crd.1 - 1)) {
            result.push(Crd(crd.0, crd.1 - 1));
        }
        if crd.0 + 1 < grid.len() && is_walkable(Crd(crd.0 + 1, crd.1)) {
            result.push(Crd(crd.0 + 1, crd.1));
        }
        if crd.1 + 1 < grid[0].len() && is_walkable(Crd(crd.0, crd.1 + 1)) {
            result.push(Crd(crd.0, crd.1 + 1));
        }
        result
    };

    let crds_of = |x: char| -> Vec<Crd> {
        let mut result = vec![];
        for (i, row) in grid.iter().enumerate() {
            for (j, cell) in row.iter().enumerate() {
                if *cell == x {
                    result.push(Crd(i, j));
                }
            }
        }
        result
    };

    let e_crd = crds_of('E')[0];

    let mut result = INF;

    for s_crd in crds_of('S') {
        let mut distance: HashMap<Crd, u16> = HashMap::new();
        distance.insert(s_crd, 0);

        let mut q: BTreeSet<(u16, usize, usize)> = BTreeSet::new();
        q.insert((0, s_crd.0, s_crd.1));

        while let Some((_, ro0, co0)) = q.pop_first() {
            for crd in adjacent_of(Crd(ro0, co0)) {
                let crd0 = Crd(ro0, co0);
                let l0 = level_at(crd0);
                let l = level_at(crd);
                let len = levels_diff(l0, l) + 1;

                if distance.get(&crd0).unwrap_or(&INF) + len < *distance.get(&crd).unwrap_or(&INF) {
                    distance.insert(crd, distance[&crd0] + len);
                    q.insert((distance[&crd], crd.0, crd.1));
                }
            }
        }

        result = result.min(*distance.get(&e_crd).unwrap());
    }
    println!("{}", result);
}
