use proconio::input;
use proconio_derive::fastout;
use std::sync::OnceLock;

const MAX_N: usize = 500_000;

static NSUM: OnceLock<Vec<usize>> = OnceLock::new();

fn get_memo() -> &'static [usize] {
    NSUM.get_or_init(|| {
        (0..=MAX_N)
            .scan(0usize, |state, k| {
                *state += k;
                Some(*state)
            })
            .collect()
    })
}

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
    let nsum: &[usize] = get_memo();
    let mut result = vec![];
    let mut s: usize = 0;
    let mut k: usize = 0;
    let mut leaps = false;

    for (i, &x) in xs.iter().enumerate() {
        if k != 0
            && ((nsum[k] == s && nsum[k + 1] != s + x)
                || (leaps && nsum[k] == s && (xs[i - 1] > x || xs[i - 1].abs_diff(x) != 1)))
        {
            let i0: usize = result.last().map_or(0, |(_, prev_end)| *prev_end);

            result.push((i0, i0 + k));
            s = 0;
            k = 0;
            leaps = false;
        }

        s += x;
        k += 1;
        if i != 0 && (xs[i - 1] > x || xs[i - 1].abs_diff(x) != 1) {
            leaps = true;
        }
    }

    let i0: usize = result.last().map_or(0, |(_, prev_end)| *prev_end);
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

    let ppp_kk: Vec<(isize, isize)> = perm_boundaries(&xs)
        .into_iter()
        .map(|(i, j)| (roation_phase(&xs[i..j]) as isize, (j - i) as isize))
        .collect();

    let mut sigma_p: isize = 0;

    for (p_prime, k) in ppp_kk.into_iter().rev() {
        let p = (((p_prime - sigma_p) % k) + k) % k;
        sigma_p += p;

        result.extend(vec![Op::Rotate; p as usize]);
        result.push(Op::Append(k as usize));
    }

    result.reverse();
    result
}

#[allow(dead_code)]
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

        //let ys = xs.clone();
        //eprintln!("ys: {:?}", ys);

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
        let xs = [1, 2, 3, 3, 4, 1, 2];
        assert_eq!(perm_boundaries(&xs), vec![(0, 3), (3, 7)], "xs: {:?}", xs);
    }

    #[test]
    fn test_perm_boundaries_c() {
        let xs = [4, 1, 2, 3];
        assert_eq!(perm_boundaries(&xs), vec![(0, 4)], "xs: {:?}", xs);
    }

    #[test]
    fn test_perm_boundaries_d() {
        let xs = [2, 3, 4, 1, 1, 2];
        assert_eq!(perm_boundaries(&xs), vec![(0, 4), (4, 6)], "xs: {:?}", xs);
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
