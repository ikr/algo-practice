use itertools::Itertools;
use proconio::input;
use proconio_derive::fastout;

fn cross_product(xy1: (i64, i64), xy2: (i64, i64)) -> i64 {
    let (x1, y1) = xy1;
    let (x2, y2) = xy2;
    x1 * y2 - y1 * x2
}

fn vector_of(xy1: (i64, i64), xy2: (i64, i64)) -> (i64, i64) {
    let (x1, y1) = xy1;
    let (x2, y2) = xy2;
    (x2 - x1, y2 - y1)
}

fn outliers_exact(xys: &[(i64, i64)]) -> usize {
    let mut result: usize = usize::MAX;
    for points_pair in xys.iter().enumerate().combinations(2) {
        let [(i0, xy1), (j0, xy2)] = points_pair[..] else {
            panic!("{:?} isn't an enumerated pair", points_pair);
        };
        let v0 = vector_of(*xy1, *xy2);

        let cur = xys
            .iter()
            .enumerate()
            .filter(|(i, _)| *i != i0 && *i != j0)
            .filter(|(_, xy)| {
                let v1 = vector_of(**xy, *xy1);
                cross_product(v0, v1) != 0
            })
            .count();
        result = result.min(cur);
    }
    result
}

fn outliers_estimation(xys: &[(i64, i64)]) -> usize {
    outliers_exact(xys)
}

#[fastout]
fn main() {
    input! {
        cases_num: u8,
    }

    for t in 1..=cases_num {
        input! {
            n: usize,
            xys: [(i64, i64); n],
        }

        eprintln!("{:?}", xys);

        let result = outliers_estimation(&xys);
        println!("Case #{}: {}", t, result);
    }
}
