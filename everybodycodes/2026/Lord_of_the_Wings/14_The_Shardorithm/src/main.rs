use std::io::{BufRead, stdin};

use ac_library::Dsu;

fn main() {
    let grid: Vec<Vec<char>> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

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

    let result: Vec<usize> = dsu
        .groups()
        .into_iter()
        .map(|group| {
            group
                .into_iter()
                .map(|u| {
                    let mut a = 0;
                    let (i, j) = (u / width, u % width);
                    let cell = grid[i][j];

                    if i == 0 || grid[i - 1][j] != cell {
                        a += 1;
                    }

                    if j == width - 1 || grid[i][j + 1] != cell {
                        a += 1;
                    }

                    if i == height - 1 || grid[i + 1][j] != cell {
                        a += 1;
                    }

                    if j == 0 || grid[i][j - 1] != cell {
                        a += 1;
                    }

                    a
                })
                .sum::<usize>()
        })
        .collect();

    eprintln!("{result:?}");
}
