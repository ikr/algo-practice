use std::collections::HashSet;

use proconio::input;
use proconio_derive::fastout;

#[derive(Clone, Copy)]
enum Op {
    Append(usize),
    Rotate,
}

impl Op {
    fn represent(self) -> String {
        match self {
            Self::Append(k) => format!("1 {k}"),
            Self::Rotate => 2.to_string(),
        }
    }
}

fn perm_boundaries(xs: &[usize]) -> Vec<(usize, usize)> {
    let mut seen: HashSet<usize> = HashSet::new();
    let mut result = vec![];

    for &x in xs {
        if seen.contains(&x) {
            let i0: usize = result.last().map_or(0, |(_, prev_end)| *prev_end);
            let k = seen.len();

            result.push((i0, i0 + k));
            seen.clear();
        }
        seen.insert(x);
    }

    let i0: usize = result.last().map_or(0, |(_, prev_end)| *prev_end);
    let k = seen.len();
    result.push((i0, i0 + k));

    result
}

fn deconstruct_program(xs: Vec<usize>) -> Vec<Op> {
    vec![Op::Append(3), Op::Rotate]
}

#[fastout]
fn main() {
    input! {
        cases_num: u16,
    }

    for t in 1..=cases_num {
        input! {
            n: usize,
            xs: [usize; n],
        }

        let result = deconstruct_program(xs);
        assert!(result.len() <= 2 * n);
        println!("Case #{t}: {}", result.len());

        for op in result {
            println!("{}", op.represent());
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_perm_boundaries_a() {
        assert_eq!(perm_boundaries(&[1]), vec![(0, 1)]);
    }

    #[test]
    fn test_perm_boundaries_b() {
        assert_eq!(
            perm_boundaries(&[1, 2, 3, 3, 4, 1, 2]),
            vec![(0, 3), (3, 7)]
        );
    }

    #[test]
    fn test_perm_boundaries_c() {
        assert_eq!(perm_boundaries(&[4, 3, 2, 1]), vec![(0, 4)]);
    }

    #[test]
    fn test_perm_boundaries_d() {
        assert_eq!(
            perm_boundaries(&[4, 3, 2, 1, 1, 1, 2]),
            vec![(0, 4), (4, 5), (5, 7)]
        );
    }
}
