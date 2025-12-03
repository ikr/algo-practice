use std::{
    io::{BufRead, stdin},
    ops::{Add, Mul, Sub},
};

const INF: u32 = 100_000_000;

fn decode_triplet(s: &str) -> (usize, usize, usize) {
    let parts: Vec<usize> = s.split(',').map(|x| x.parse().unwrap()).collect();
    (parts[0], parts[1], parts[2])
}

fn walls_and_windows_from_triplets(
    triplests: Vec<(usize, usize, usize)>,
) -> (Vec<usize>, Vec<(usize, usize)>) {
    let mut walls = vec![];
    let mut windows = vec![];

    for (col, first_row, window_height) in triplests {
        walls.push(col);
        windows.push((first_row, first_row + window_height - 1));
    }

    (walls, windows)
}

fn is_passable(walls: &[usize], windows: &[(usize, usize)], crd: (usize, usize)) -> bool {
    let (row, col) = crd;
    let ii: Vec<usize> = walls
        .iter()
        .enumerate()
        .filter_map(|(i, &wall_col)| if wall_col == col { Some(i) } else { None })
        .collect();

    if ii.is_empty() {
        true
    } else {
        ii.into_iter().any(|i| {
            let (row_lo, row_hi) = windows[i];
            row_lo <= row && row <= row_hi
        })
    }
}

fn vec_add<T>(a: Vec<T>, b: Vec<T>) -> Vec<T>
where
    T: Add<Output = T>,
{
    assert_eq!(a.len(), b.len());
    a.into_iter().zip(b).map(|(x, y)| x + y).collect()
}

fn vec_sub<T>(a: Vec<T>, b: Vec<T>) -> Vec<T>
where
    T: Sub<Output = T>,
{
    assert_eq!(a.len(), b.len());
    a.into_iter().zip(b).map(|(x, y)| x - y).collect()
}

fn vec_scale_by_k<T>(a: Vec<T>, k: T) -> Vec<T>
where
    T: Mul<Output = T> + Copy,
{
    a.into_iter().map(|x| x * k).collect()
}

#[allow(clippy::needless_range_loop)]
fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();

    let triplests: Vec<(usize, usize, usize)> = lines
        .into_iter()
        .map(|line| decode_triplet(&line))
        .collect();

    let (walls, windows) = walls_and_windows_from_triplets(triplests);
    let h = (windows.iter().map(|(_, row_hi)| row_hi).max().unwrap() * 3) / 2;
    let w = walls.last().unwrap() + 1;

    let mut tab: Vec<u32> = vec![INF; h];
    tab[0] = 0;

    for col in 0..w - 1 {
        let mut new_tab: Vec<u32> = vec![INF; h];

        for row in 0..h {
            if row != 0 && is_passable(&walls, &windows, (row - 1, col + 1)) {
                new_tab[row - 1] = new_tab[row - 1].min(tab[row]);
            }

            if row != h - 1 && is_passable(&walls, &windows, (row + 1, col + 1)) {
                new_tab[row + 1] = new_tab[row + 1].min(tab[row] + 1);
            }
        }

        tab = new_tab;
    }
    eprintln!();

    let result = tab.into_iter().min().unwrap();
    println!("{result}");
}
