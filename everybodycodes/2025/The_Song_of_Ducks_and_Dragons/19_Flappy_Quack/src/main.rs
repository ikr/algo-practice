use std::{
    collections::BTreeMap,
    io::{BufRead, stdin},
    ops::{Add, Mul, Sub},
};

const INF: u32 = 100_000_000;

type Windows = Vec<(usize, usize)>;
type Walls = BTreeMap<usize, Windows>;

fn decode_triplet(s: &str) -> (usize, usize, usize) {
    let parts: Vec<usize> = s.split(',').map(|x| x.parse().unwrap()).collect();
    (parts[0], parts[1], parts[2])
}

fn walls_from_triplets(triplets: Vec<(usize, usize, usize)>) -> Walls {
    triplets.into_iter().fold(
        BTreeMap::new(),
        |mut acc, (col, first_row, window_height)| {
            let window = (first_row, first_row + window_height - 1);
            acc.entry(col)
                .and_modify(|windows| windows.push(window))
                .or_insert(vec![window]);
            acc
        },
    )
}

fn is_passable(walls: &Walls, crd: (usize, usize)) -> bool {
    let (row, col) = crd;
    if let Some(windows) = walls.get(&col) {
        windows
            .iter()
            .any(|&(row_lo, row_hi)| row_lo <= row && row <= row_hi)
    } else {
        true
    }
}

fn vec_add<T>(a: Vec<T>, b: Vec<T>) -> Vec<T>
where
    T: Add<Output = T> + Copy,
{
    assert_eq!(a.len(), b.len());
    a.into_iter().zip(b).map(|(x, y)| x + y).collect()
}

fn vec_sub<T>(a: Vec<T>, b: &[T]) -> Vec<T>
where
    T: Sub<Output = T> + Copy,
{
    assert_eq!(a.len(), b.len());
    a.into_iter().zip(b).map(|(x, &y)| x - y).collect()
}

fn vec_scale_by_k<T>(a: Vec<T>, k: T) -> Vec<T>
where
    T: Mul<Output = T> + Copy,
{
    a.into_iter().map(|x| x * k).collect()
}

fn strictly_containing_columns_interval(wall_cols: &[usize], col: usize) -> Option<(usize, usize)> {
    wall_cols.binary_search(&col).is_err().then(|| {
        let j = wall_cols.partition_point(|&wall_col| wall_col <= col);
        assert_ne!(j, 0);
        (wall_cols[j - 1], wall_cols[j])
    })
}

fn next_dp_state(h: usize, walls: &Walls, col: usize, tab: Vec<u32>) -> Vec<u32> {
    let mut result: Vec<u32> = vec![INF; h];

    for row in 0..h {
        if row != 0 && is_passable(walls, (row - 1, col + 1)) {
            result[row - 1] = result[row - 1].min(tab[row]);
        }

        if row != h - 1 && is_passable(walls, (row + 1, col + 1)) {
            result[row + 1] = result[row + 1].min(tab[row] + 1);
        }
    }
    result
}

#[allow(clippy::needless_range_loop)]
fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();

    let triplets: Vec<(usize, usize, usize)> = lines
        .into_iter()
        .map(|line| decode_triplet(&line))
        .collect();

    let max_col: usize = triplets.iter().map(|&(co, _, _)| co).max().unwrap();

    let max_row: usize = triplets
        .iter()
        .map(|(_, ro, delta)| ro + delta - 1)
        .max()
        .unwrap();

    let walls = walls_from_triplets(triplets);
    let wall_cols: Vec<usize> = walls.keys().copied().collect();
    let h = (max_row * 3) / 2;
    let w = max_col + 1;

    let mut tab: Vec<u32> = vec![INF; h];
    tab[0] = 0;
    let mut col: usize = 0;

    while col != w - 1 {
        if wall_cols[0] < col
            && let Some((col1, col2)) = strictly_containing_columns_interval(&wall_cols, col)
            && col2 - col1 > 4
        {
            let new_tab = next_dp_state(h, &walls, col, tab.clone());
            let leap: Vec<u32> = vec_scale_by_k(vec_sub(new_tab, &tab), (col2 - col1 - 1) as u32);
            tab = vec_add(tab, leap);
            col += col2 - col1 - 1;
        } else {
            tab = next_dp_state(h, &walls, col, tab);
            col += 1;
        }
    }

    let result = tab.into_iter().min().unwrap();
    println!("{result}");
}
