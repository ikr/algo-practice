use ac_library::Dsu;
use itertools::Itertools;
use proconio::{input, marker::Usize1};
use std::cmp::Ordering;
use std::io::{BufWriter, Write, stdout};

fn iof(x: bool) -> i64 {
    if x { 1 } else { 0 }
}

#[derive(Clone, Copy)]
struct Angle {
    x: i64,
    y: i64,
}

impl Angle {
    fn from(xy: (i64, i64)) -> Self {
        let (x, y) = xy;
        Self { x, y }
    }

    fn half(self) -> i64 {
        assert!(self.x != 0 || self.y != 0);
        iof(self.y < 0 || (self.y == 0 && self.x < 0))
    }

    fn is_less(self, other: Self) -> bool {
        let a = self;
        let b = other;
        (a.half(), a.y * b.x) < (b.half(), a.x * b.y)
    }

    fn cmp(self, other: Self) -> Ordering {
        if self.is_less(other) {
            Ordering::Less
        } else if other.is_less(self) {
            Ordering::Greater
        } else {
            Ordering::Equal
        }
    }
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        q: usize,
        ps: [(i64, i64); n],
        ij: [(Usize1, Usize1); q],
    }

    let mut angles: Vec<Angle> = ps.into_iter().map(Angle::from).collect();
    angles.sort_by(|&a, &b| b.cmp(a));

    let mut eq_classes: Dsu =
        (0..n)
            .tuple_windows::<(_, _)>()
            .fold(Dsu::new(angles.len()), |mut acc, (i, j)| {
                if angles[i].cmp(angles[j]) == Ordering::Equal {
                    acc.merge(i, j);
                }
                acc
            });

    let mut groups: Vec<Vec<usize>> = eq_classes.groups();
    groups.sort_by(|g, h| angles[h[0]].cmp(angles[g[0]]));

    let group_index_by_angle_index: Vec<usize> = {
        let mut result = vec![usize::MAX; n];

        for (gi, ais) in groups.iter().enumerate() {
            for ai in ais {
                result[*ai] = gi;
            }
        }

        result
    };

    let m = groups.len();
    let group_sizes_cumsum: Vec<usize> = groups
        .into_iter()
        .scan(0, |acc, g| {
            *acc += g.len();
            Some(*acc)
        })
        .collect();

    let inc_range_sum = |i: usize, j: usize| -> usize {
        group_sizes_cumsum[j] - if i == 0 { 0 } else { group_sizes_cumsum[i - 1] }
    };

    for (i, j) in ij {
        let gi = group_index_by_angle_index[i];
        let gj = group_index_by_angle_index[j];

        let result = if gi <= gj {
            inc_range_sum(gi, gj)
        } else {
            inc_range_sum(gi, m - 1) + group_sizes_cumsum[gj]
        };
        writeln!(writer, "{result}").unwrap();
    }

    writer.flush().unwrap();
}
