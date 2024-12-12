use ac_library::Dsu;
use std::{
    collections::BTreeSet,
    io::{self, BufRead},
};

fn number_of_sides(ps: &[(i16, i16)]) -> usize {
    let v = ps.iter().collect::<Vec<_>>();

    let index_of = |p: (i16, i16)| v.iter().position(|&q| *q == p).unwrap();

    let neighs_of = |i: usize| -> Vec<usize> {
        let p = v.iter().find(|&&p| p.0 == v[i].0 && p.1 == v[i].1).unwrap();
        let ro = p.0;
        let co = p.1;

        let mut ret: Vec<usize> = Vec::new();
        if ps.contains(&(ro - 1, co)) {
            ret.push(index_of((ro - 1, co)));
        }
        if ps.contains(&(ro, co - 1)) {
            ret.push(index_of((ro, co - 1)));
        }
        if ps.contains(&(ro + 1, co)) {
            ret.push(index_of((ro + 1, co)));
        }
        if ps.contains(&(ro, co + 1)) {
            ret.push(index_of((ro, co + 1)));
        }
        ret
    };

    let mut dsu = Dsu::new(v.len());
    for i in 0..v.len() {
        for &j in neighs_of(i).iter() {
            dsu.merge(i, j);
        }
    }
    dsu.groups().len()
}

fn main() {
    let grid: Vec<Vec<u8>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().bytes().collect())
        .collect();

    let h = grid.len();
    let w = grid[0].len();

    let code_of = |ro: usize, co: usize| -> usize { ro * w + co };

    let crd_of = |code: usize| -> (usize, usize) { (code / w, code % w) };

    let adjacent_of = |ro: usize, co: usize| -> Vec<(usize, usize)> {
        let x = grid[ro][co];
        let mut adjacent = Vec::new();
        if ro != 0 && grid[ro - 1][co] == x {
            adjacent.push((ro - 1, co));
        }
        if co != 0 && grid[ro][co - 1] == x {
            adjacent.push((ro, co - 1));
        }
        if ro != h - 1 && grid[ro + 1][co] == x {
            adjacent.push((ro + 1, co));
        }
        if co != w - 1 && grid[ro][co + 1] == x {
            adjacent.push((ro, co + 1));
        }
        adjacent
    };

    let border_crds = |ro: usize, co: usize| -> BTreeSet<(i16, i16)> {
        let adj: Vec<(i16, i16)> = adjacent_of(ro, co)
            .into_iter()
            .map(|(ro2, co2)| (ro2 as i16, co2 as i16))
            .collect();

        let iro = ro as i16;
        let ico = co as i16;
        [
            (iro - 1, ico),
            (iro, ico - 1),
            (iro + 1, ico),
            (iro, ico + 1),
        ]
        .into_iter()
        .filter(|crd| !adj.contains(crd))
        .collect()
    };

    let mut dsu = Dsu::new(h * w);

    for ro in 0..h {
        for co in 0..w {
            for &(ro2, co2) in adjacent_of(ro, co).iter() {
                dsu.merge(code_of(ro, co), code_of(ro2, co2));
            }
        }
    }

    let borders_num_of = |ro: usize, co: usize| -> usize { 4 - adjacent_of(ro, co).len() };

    let mut result: usize = 0;
    for codes in dsu.groups() {
        let area = codes.len();
        let border: Vec<(i16, i16)> = codes
            .iter()
            .map(|&code| {
                let crd = crd_of(code);
                border_crds(crd.0, crd.1)
            })
            .fold(vec![], |mut acc, xs| {
                acc.extend(xs);
                acc
            });
        let num_sides = number_of_sides(&border);
        eprintln!("{:?} {:?} {:?}", border, area, num_sides);
        result += area * num_sides;
    }
    println!("{}", result);
}
