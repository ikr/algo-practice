use ac_library::Dsu;
use itertools::Itertools;
use std::{
    cmp::Reverse,
    collections::{BinaryHeap, HashMap, HashSet},
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

fn components_edges(
    grid_height: usize,
    grid_width: usize,
    cs: Vec<Vec<usize>>,
) -> BinaryHeap<Reverse<(u8, usize, usize)>> {
    let component_by_cell_id =
        |cell_id: usize| cs.iter().position(|c| c.contains(&cell_id)).unwrap();

    let mut seams: HashMap<(usize, usize), HashSet<(usize, usize)>> = HashMap::new();

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

                seams
                    .entry((u_c.min(v_c), u_c.max(v_c)))
                    .and_modify(|cell_edges| {
                        cell_edges.insert((u.min(v), u.max(v)));
                    })
                    .or_insert(HashSet::from([(u.min(v), u.max(v))]));
            }
        }
    }

    seams
        .into_iter()
        .map(|((u, v), u_cs)| Reverse((u_cs.len() as u8, u, v)))
        .collect()
}

fn additional_bindings_num(
    n: usize,
    charged: [usize; 2],
    mut pq: BinaryHeap<Reverse<(u8, usize, usize)>>,
) -> u16 {
    let mut dsu = Dsu::new(n);
    let mut result: u16 = 0;

    while let Some(Reverse((w, u, v))) = pq.pop() {
        if (!charged.contains(&u) && !charged.contains(&v)) && !dsu.same(u, v) {
            result += w as u16;
        }

        dsu.merge(u, v);
    }

    result
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
    assert!(cs[0].contains(&0));
    let n = cs.len();
    let pq = components_edges(grid.len(), grid[0].len(), cs);

    let result: u16 = (1..n)
        .array_combinations()
        .map(|[u, v]| additional_bindings_num(n, [u, v], pq.clone()))
        .min()
        .unwrap();

    println!("{result}");
}
