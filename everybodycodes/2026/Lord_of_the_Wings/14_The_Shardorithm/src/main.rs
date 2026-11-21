use ac_library::Dsu;
use std::io::{BufRead, stdin};

fn wrap_into_frame(mut grid: Vec<Vec<char>>) -> Vec<Vec<char>> {
    for row in &mut grid {
        row.insert(0, '~');
        row.push('~');
    }

    let width = grid[0].len();
    grid.insert(0, vec!['~'; width]);
    grid.push(vec!['~'; width]);

    grid
}

fn connected_components(grid: &[Vec<char>]) -> Vec<Vec<usize>> {
    let height = grid.len();
    let width = grid[0].len();
    let mut dsu = Dsu::new(height * width);

    for (i, row) in grid.iter().enumerate() {
        for (j, &cell) in row.iter().enumerate() {
            let u = i * width + j;

            if i != 0 && grid[i - 1][j] == cell {
                dsu.merge(u, (i - 1) * width + j);
            }

            if j != width - 1 && grid[i][j + 1] == cell {
                dsu.merge(u, i * width + j + 1);
            }

            if i != height - 1 && grid[i + 1][j] == cell {
                dsu.merge(u, (i + 1) * width + j);
            }

            if j != 0 && grid[i][j - 1] == cell {
                dsu.merge(u, i * width + j - 1);
            }
        }
    }

    dsu.groups()
}

fn components_adjacency_graph(grid: &[Vec<char>], cs: Vec<Vec<usize>>) -> Vec<Vec<(usize, u8)>> {
    let height = grid.len();
    let width = grid[0].len();
    todo!()
}

fn main() {
    let grid: Vec<Vec<char>> = wrap_into_frame(
        stdin()
            .lock()
            .lines()
            .map(|line| line.unwrap().chars().collect())
            .collect(),
    );

    let cs = connected_components(&grid);
}
