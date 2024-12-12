use ac_library::Dsu;
use itertools::Itertools;
use std::io::{self, BufRead};

fn split_border_crds_into_vert_and_horz(
    p: (i16, i16),
    border: &[(i16, i16)],
) -> (Vec<(i16, i16)>, Vec<(i16, i16)>) {
    let up = (p.0 - 1, p.1);
    let right = (p.0, p.1 + 1);
    let down = (p.0 + 1, p.1);
    let left = (p.0, p.1 - 1);

    match border.iter().cloned().sorted().collect::<Vec<_>>()[..] {
        [x] if x == up || x == down => (vec![], vec![x]),
        [x] if x == left || x == right => (vec![x], vec![]),
        [x, y] if x == up && y == down => (vec![], vec![x, y]),
        [x, y] if x == left && y == right => (vec![x, y], vec![]),
        [x, y] if x == up && y == right => (vec![y], vec![x]),
        [x, y] if x == right && y == down => (vec![x], vec![y]),
        [x, y] if x == left && y == down => (vec![x], vec![y]),
        [x, y] if x == up && y == left => (vec![y], vec![x]),
        [x, y, z] if x == left && y == right && z == down => (vec![x, y], vec![z]),
        [x, y, z] if x == up && y == left && z == down => (vec![y], vec![x, z]),
        [x, y, z] if x == up && y == left && z == right => (vec![y, z], vec![x]),
        [x, y, z] if x == up && y == right && z == down => (vec![y], vec![x, z]),
        [w, x, y, z] => (vec![x, y], vec![w, z]),
        _ => panic!("Unexpected border {:?} for {:?}", p, border),
    }
}

fn count_breaks(ps: &[(i16, i16)]) -> usize {
    ps.windows(2)
        .filter(|&pq| {
            let p = pq[0];
            let q = pq[1];
            p.0.abs_diff(q.0) + p.1.abs_diff(q.1) == 1
        })
        .count()
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

    let border_crds = |ro: usize, co: usize| -> Vec<(i16, i16)> {
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

    let mut result = 0;
    for codes in dsu.groups() {
        let mut vert_border_by_level: Vec<Vec<(i16, i16)>> = vec![vec![]; w];
        let mut horz_border_by_level: Vec<Vec<(i16, i16)>> = vec![vec![]; h];

        for &code in codes.iter() {
            let crd = crd_of(code);
            let (vert, horz) = split_border_crds_into_vert_and_horz(
                (crd.0 as i16, crd.1 as i16),
                &border_crds(crd.0, crd.1),
            );
            vert_border_by_level[crd.1].extend(vert);
            horz_border_by_level[crd.0].extend(horz);
        }

        let mut sides = 0;

        for ps in vert_border_by_level.iter_mut() {
            ps.sort();
            sides += count_breaks(ps);
        }

        for ps in horz_border_by_level.iter_mut() {
            ps.sort();
            sides += count_breaks(ps) + 1;
        }

        let area = codes.len();
        eprintln!("area:{} sides:{}", area, sides);
        result += area * sides;
    }
    println!("{}", result);
}
