use ac_library::Dsu;
use std::io::{self, BufRead};

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
        let perimeter = codes
            .iter()
            .map(|&code| {
                let crd = crd_of(code);
                borders_num_of(crd.0, crd.1)
            })
            .sum::<usize>();
        eprintln!("area = {}, perimeter = {}", area, perimeter);
        result += area * perimeter;
    }
    println!("{}", result);
}
