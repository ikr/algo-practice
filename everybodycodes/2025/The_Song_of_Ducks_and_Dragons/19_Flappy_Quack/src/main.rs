use itertools::Itertools;
use std::{
    collections::BTreeMap,
    io::{BufRead, stdin},
};

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i64, i64);

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}
type Windows = Vec<(i64, i64)>;
type Walls = BTreeMap<i64, Windows>;

fn decode_triplet(s: &str) -> (i64, i64, i64) {
    s.split(',')
        .map(|x| x.parse().unwrap())
        .collect_tuple()
        .unwrap()
}

fn walls_from_triplets(triplets: Vec<(i64, i64, i64)>) -> Walls {
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
fn strictly_containing_columns_interval(wall_cols: &[i64], col: i64) -> Option<(i64, i64)> {
    wall_cols.binary_search(&col).is_err().then(|| {
        let j = wall_cols.partition_point(|&wall_col| wall_col <= col);
        assert_ne!(j, 0);
        (wall_cols[j - 1], wall_cols[j])
    })
}

#[allow(clippy::needless_range_loop)]
fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();

    let triplets = lines
        .into_iter()
        .map(|line| decode_triplet(&line))
        .collect();

    let walls = walls_from_triplets(triplets);
    let wall_cols: Vec<i64> = walls.keys().copied().collect();
    eprintln!("{:?}", wall_cols);
}
