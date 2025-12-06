use itertools::Itertools;
use pathfinding::prelude::dijkstra;
use std::{
    collections::{BTreeMap, HashMap},
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

fn window_crds_for(window_col: i64, window_row_ranges: Windows) -> Vec<Crd> {
    window_row_ranges
        .iter()
        .flat_map(|&(a, b)| (a..=b).map(|row| Crd(row, window_col)).collect::<Vec<_>>())
        .collect()
}

fn flaps_from_a_to_b(a: Crd, b: Crd) -> Option<i64> {
    let Crd(ro_a, co_a) = a;
    let Crd(ro_b, co_b) = b;
    assert!(co_a < co_b);

    let horz_distance = co_b - co_a;
    let max_reachable_ro = ro_a + horz_distance;
    let min_reachable_ro = ro_a - horz_distance;
    let offset = ro_b - min_reachable_ro;

    (min_reachable_ro <= ro_b && ro_b <= max_reachable_ro && offset % 2 == 0).then_some(offset / 2)
}

fn graph_from(window_crds: Vec<Vec<Crd>>) -> HashMap<Crd, Vec<(Crd, i64)>> {
    let mut result = HashMap::new();
    let start = Crd(0, 0);

    for &b in &window_crds[0] {
        let mut vs: Vec<(Crd, i64)> = vec![];
        if let Some(w) = flaps_from_a_to_b(start, b) {
            vs.push((b, w))
        }
        result.insert(start, vs);
    }

    for (us, vs) in window_crds.into_iter().tuple_windows() {
        for (u, v) in us.into_iter().cartesian_product(vs) {
            if let Some(w) = flaps_from_a_to_b(u, v) {
                let e = (v, w);

                result
                    .entry(u)
                    .and_modify(|vs| vs.push(e))
                    .or_insert(vec![e]);
            }
        }
    }

    result
}

// ......X
// .....*#
// ....*.X
// ...*.*#
// ..*.*.*
// .*...*.*
// *.....*.*
// .......*.*
//
fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();

    let triplets = lines
        .into_iter()
        .map(|line| decode_triplet(&line))
        .collect();

    let walls = walls_from_triplets(triplets);
    let max_col: i64 = *walls.keys().last().unwrap();

    let window_crds: Vec<Vec<Crd>> = walls
        .into_iter()
        .map(|(co, windows)| window_crds_for(co, windows))
        .collect();

    let g = graph_from(window_crds);

    let result: i64 = dijkstra(
        &Crd(0, 0),
        |u| g.get(u).unwrap_or(&vec![]).clone(),
        |u| u.1 == max_col,
    )
    .unwrap()
    .1;

    println!("{result}");
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_flaps_from_a_to_b() {
        for (a, b, expected) in [
            (Crd(0, 0), Crd(7, 7), Some(7)),
            (Crd(7, 7), Crd(2, 12), Some(0)),
        ] {
            assert_eq!(flaps_from_a_to_b(a, b), expected, "{:?} → {:?}", a, b);
        }
    }
}
