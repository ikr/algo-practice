use ac_library::Dsu;
use std::{
    collections::{HashMap, HashSet},
    io::{BufRead, stdin},
};

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

fn components_adjacency_graph(
    grid_height: usize,
    grid_width: usize,
    cs: Vec<Vec<usize>>,
) -> Vec<Vec<(usize, u8)>> {
    let mut graph: Vec<Vec<(usize, u8)>> = vec![vec![]; cs.len()];

    let component_by_cell_id =
        |cell_id: usize| cs.iter().position(|c| c.contains(&cell_id)).unwrap();

    let mut unique_edges: HashMap<(usize, usize), HashSet<(usize, usize)>> = HashMap::new();

    for i in 0..grid_height {
        for j in 0..grid_width {
            let u = i * grid_width + j;
            let u_c = component_by_cell_id(u);

            let vs: Vec<usize> = [
                (i != 0, i.saturating_sub(1) * grid_width + j),
                (j != grid_width - 1, i * grid_width + j + 1),
                (i != grid_height - 1, (i + 1) * grid_width + j),
                (j != 0, i * grid_width + j.saturating_sub(1)),
            ]
            .into_iter()
            .filter_map(|(pred, v)| (pred && component_by_cell_id(v) != u_c).then_some(v))
            .collect();

            for v in vs {
                let v_c = component_by_cell_id(v);
                assert_ne!(v_c, u_c);

                unique_edges
                    .entry((u_c.min(v_c), u_c.max(v_c)))
                    .and_modify(|cell_edges| {
                        cell_edges.insert((u.min(v), u.max(v)));
                    })
                    .or_insert(HashSet::from([(u.min(v), u.max(v))]));
            }
        }
    }

    eprintln!("UQs:{unique_edges:?}");
    graph
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
    eprintln!("{cs:?}");
    let g = components_adjacency_graph(grid.len(), grid[0].len(), cs);
    eprintln!("{g:?}");
}
