use num_integer::lcm;
use proconio::input;
use proconio_derive::fastout;
use std::collections::HashSet;

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

fn roation_phase(xs: &[usize]) -> usize {
    let n = xs.len();
    let i1 = xs.iter().position(|x| *x == 1).unwrap();
    (n - i1) % n
}

fn deconstruct_program(xs: Vec<usize>) -> Vec<Op> {
    let mut result = vec![];
    let mut global_p: usize = 0;
    let ii = perm_boundaries(&xs);
    let m: usize = ii
        .iter()
        .map(|(i, j)| j - i)
        .reduce(|acc, k| lcm(acc, k))
        .unwrap();

    for (i, j) in ii.into_iter().rev() {
        let k = j - i;
        let p0 = roation_phase(&xs[i..j]);
        global_p += p0;
        global_p %= m;

        result.extend(vec![Op::Rotate; global_p]);
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

        let result = deconstruct_program(xs);

        //verify_program(&result, &ys);
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
