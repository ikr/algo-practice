use std::io::{self, BufRead};

#[derive(Debug, Clone, Copy)]
enum Dir {
    N,
    E,
    S,
    W,
}

#[derive(Debug, Clone, Copy)]
struct Roco(usize, usize);

fn index_of_entrance(top_row: &[char]) -> usize {
    top_row.iter().position(|&x| x == '|').unwrap()
}

fn dimensions(grid: &[Vec<char>]) -> Roco {
    Roco(grid.len(), grid[0].len())
}

fn vertex_index(grid_width: usize, roco: Roco) -> usize {
    assert!(roco.1 < grid_width);
    grid_width * roco.0 + roco.1
}

fn grid_roco(grid_width: usize, v_idx: usize) -> Roco {
    Roco(v_idx / grid_width, v_idx % grid_width)
}

fn main() {
    let grid: Vec<Vec<char>> = io::stdin()
        .lock()
        .lines()
        .map(|x| x.unwrap().chars().collect())
        .collect();

    eprintln!("{:?}", grid);
    eprintln!("Dimensions: {:?}", dimensions(&grid));
    eprintln!("Entrance at column {}", index_of_entrance(&grid[0]));
}
