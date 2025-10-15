use num_integer::lcm;
use proconio::input;
use proconio_derive::fastout;
use std::{collections::BTreeSet, usize};

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
    let mut seen: BTreeSet<usize> = BTreeSet::new();
    let mut result = vec![];
    let mut lo = usize::MAX;

    for &x in xs {
        if lo == 1 && (seen.contains(&x) || (!seen.is_empty() && seen.len().abs_diff(x) > 1)) {
            let i0: usize = result.last().map_or(0, |(_, prev_end)| *prev_end);
            let k = seen.len();

            result.push((i0, i0 + k));
            seen.clear();
            lo = usize::MAX;
        }

        seen.insert(x);
        lo = lo.min(x);
    }

    let i0: usize = result.last().map_or(0, |(_, prev_end)| *prev_end);
    let k = seen.len();
    result.push((i0, i0 + k));

    result
}

fn roation_phase(xs: &[usize]) -> usize {
    let n = xs.len();
    let i1 = xs.iter().position(|x| *x == 1).unwrap();
    (n - i1) % n
}

fn deconstruct_program(xs: Vec<usize>) -> Vec<Op> {
    let mut result = vec![];

    let ppp_kk: Vec<(usize, usize)> = perm_boundaries(&xs)
        .into_iter()
        .map(|(i, j)| (roation_phase(&xs[i..j]), j - i))
        .collect();

    let m: usize = ppp_kk.iter().map(|(_, k)| *k).reduce(lcm).unwrap();

    let mut sigma_p: usize = 0;

    for (p_prime, k) in ppp_kk.into_iter().rev() {
        let p = (p_prime + m - sigma_p) % k;
        sigma_p += p;
        sigma_p %= m;

        result.extend(vec![Op::Rotate; p]);
        result.push(Op::Append(k));
    }

    result.reverse();
    result
}

fn verify_program(ops: &[Op], expected_result: &[usize]) {
    let mut xss: Vec<Vec<usize>> = vec![];

    for &op in ops {
        match op {
            Op::Append(k) => xss.push((1..=k).collect()),
            Op::Rotate => {
                for xs in &mut xss {
                    xs.rotate_left(1);
                }
            }
        }
    }

    assert_eq!(
        xss.iter().flatten().cloned().collect::<Vec<_>>(),
        expected_result
    );
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

        let ys = xs.clone();
        eprintln!("ys: {:?}", ys);

        let result = deconstruct_program(xs);

        verify_program(&result, &ys);
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
        let xs = [1, 2, 3, 3, 4, 1, 2];
        assert_eq!(perm_boundaries(&xs), vec![(0, 3), (3, 7)], "xs: {:?}", xs);
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

    #[test]
    fn test_perm_boundaries_e() {
        let xs = [2, 3, 4, 5, 1, 14, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13];
        assert_eq!(perm_boundaries(&xs), vec![(0, 5), (5, 19)], "xs: {:?}", xs);
    }

    #[test]
    fn test_perm_boundaries_f() {
        assert_eq!(perm_boundaries(&[1, 1, 1]), vec![(0, 1), (1, 2), (2, 3)]);
    }

    #[test]
    fn test_perm_boundaries_g() {
        let xs = [1, 2, 1, 1];
        assert_eq!(
            perm_boundaries(&xs),
            vec![(0, 2), (2, 3), (3, 4)],
            "xs: {:?}",
            xs
        );
    }

    #[test]
    fn test_perm_boundaries_h() {
        let xs = [1, 1, 2, 1];
        assert_eq!(
            perm_boundaries(&xs),
            vec![(0, 1), (1, 3), (3, 4)],
            "xs: {:?}",
            xs
        );
    }

    #[test]
    fn test_perm_boundaries_i() {
        let xs = [2, 3, 1, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 1, 2, 3];
        assert_eq!(perm_boundaries(&xs), vec![(0, 3), (3, 17)], "xs: {:?}", xs);
    }

    #[test]
    fn test_rotation_phase_a() {
        assert_eq!(roation_phase(&[1]), 0);
    }

    #[test]
    fn test_rotation_phase_b() {
        assert_eq!(roation_phase(&[3, 4, 1, 2]), 2);
    }

    #[test]
    fn test_rotation_phase_c() {
        assert_eq!(roation_phase(&[2, 3, 1]), 1);
    }

    #[test]
    fn test_rotation_phase_d() {
        assert_eq!(roation_phase(&[3, 1, 2]), 2);
    }

    #[test]
    fn test_rotation_phase_e() {
        assert_eq!(roation_phase(&[1, 2, 3]), 0);
    }

    #[test]
    fn test_verify_program() {
        verify_program(
            &[
                Op::Append(3),
                Op::Rotate,
                Op::Append(4),
                Op::Rotate,
                Op::Rotate,
            ],
            &[1, 2, 3, 3, 4, 1, 2],
        );
    }
}
