use std::{
    collections::VecDeque,
    io::{BufRead, stdin},
};

fn decode_triplet(s: &str) -> (u16, u16, u16) {
    let parts: Vec<u16> = s.split(',').map(|x| x.parse().unwrap()).collect();
    (parts[0], parts[1], parts[2])
}

fn walls_and_windows_from_triplets(triplests: Vec<(u16, u16, u16)>) -> (Vec<u16>, Vec<(u16, u16)>) {
    let mut walls = vec![];
    let mut windows = vec![];

    for (col, first_row, window_height) in triplests {
        walls.push(col);
        windows.push((first_row, first_row + window_height - 1));
    }

    (walls, windows)
}

fn is_passable(walls: &[u16], windows: &[(u16, u16)], crd: (u16, u16)) -> bool {
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

fn adjacent(walls: &[u16], windows: &[(u16, u16)], crd: (u16, u16)) -> Vec<((u16, u16), u16)> {
    assert!(is_passable(walls, windows, crd));
    let (row, col) = crd;
    let mut result = vec![];

    if row != 0 && is_passable(walls, windows, (row - 1, col + 1)) {
        result.push(((row - 1, col + 1), 0))
    }

    if is_passable(walls, windows, (row + 1, col + 1)) {
        result.push(((row + 1, col + 1), 1))
    }

    result
}

fn is_finish_line(walls: &[u16], windows: &[(u16, u16)], crd: (u16, u16)) -> bool {
    assert!(is_passable(walls, windows, crd));
    let n = walls.len();
    crd.1 == walls[n - 1] && is_passable(walls, windows, crd)
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();

    let triplests: Vec<(u16, u16, u16)> = lines
        .into_iter()
        .map(|line| decode_triplet(&line))
        .collect();

    let (walls, windows) = walls_and_windows_from_triplets(triplests);
    let mut q: VecDeque<((u16, u16), u16)> = VecDeque::from([((0, 0), 0)]);
    let mut result = u16::MAX;

    while let Some((u, distance)) = q.pop_front() {
        if is_finish_line(&walls, &windows, u) {
            result = result.min(distance);
        } else {
            for (v, w) in adjacent(&walls, &windows, u) {
                if w == 1 {
                    q.push_back((v, distance + 1))
                } else {
                    assert_eq!(w, 0);
                    q.push_front((v, distance))
                }
            }
        }
    }

    println!("{result}");
}
