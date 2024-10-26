use std::collections::HashSet;

use proconio::input;

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i32, i32);

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

fn jumps_from(crd: Crd) -> Vec<Crd> {
    let Crd(i, j) = crd;
    vec![
        Crd(i + 2, j + 1),
        Crd(i + 1, j + 2),
        Crd(i - 1, j + 2),
        Crd(i - 2, j + 1),
        Crd(i - 2, j - 1),
        Crd(i - 1, j - 2),
        Crd(i + 1, j - 2),
        Crd(i + 2, j - 1),
    ]
}

fn in_bounds(n: u64, crd: Crd) -> bool {
    let Crd(r, c) = crd;
    let nn = n as i32;
    0 <= r && r < nn && 0 <= c && c < nn
}

fn safe_squares_num(n: u64, ps: &[(i32, i32)]) -> u64 {
    let mut taken: HashSet<Crd> = HashSet::new();
    for (r, c) in ps {
        let crd = Crd(*r, *c);
        taken.insert(crd);

        for u in jumps_from(crd).into_iter().filter(|v| in_bounds(n, *v)) {
            taken.insert(u);
        }
    }

    n * n - (taken.len() as u64)
}

fn main() {
    input! {
        n: u64,
        m: usize,
        mut ps: [(i32, i32); m],
    }

    for (r, c) in ps.iter_mut() {
        *r -= 1;
        *c -= 1;
    }

    let result = safe_squares_num(n, &ps);
    println!("{}", result);
}
