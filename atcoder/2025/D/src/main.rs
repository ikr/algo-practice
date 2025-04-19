use itertools::Itertools;
use proconio::{input, marker::Isize1};
use std::io::{BufWriter, Write, stdout};

fn num_pairs(k: usize) -> usize {
    k * (k - 1) / 2
}

fn mod_distance_to_zero(n: isize, x: isize) -> isize {
    assert!(x < n);
    assert!(0 <= x);
    x.min(n - x)
}

fn mod_diff_to_zero(n: isize, x: isize) -> isize {
    assert!(x < n);
    assert!(0 <= x);
    if x <= n - x { -x } else { n - x }
}

fn equi_class(n: isize, ab: (isize, isize)) -> isize {
    let (a, b) = ab;
    if mod_distance_to_zero(n, a) <= mod_distance_to_zero(n, b) {
        let d = mod_diff_to_zero(n, a);
        assert!(b - d > 0 && b - d < n);
        b - d
    } else {
        let d = mod_diff_to_zero(n, b);
        assert!(a - d > 0 && a - d < n);
        a - d
    }
}

fn solve(n: isize, ab: &[(isize, isize)]) -> usize {
    if n % 2 != 0 {
        return num_pairs(ab.len());
    }

    let fq = ab.iter().map(|ab| equi_class(n, *ab)).counts();
    let mut result = num_pairs(ab.len());
    for (_, f) in fq {
        result -= num_pairs(f);
    }
    result
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: isize,
        m: usize,
        ab: [(Isize1, Isize1); m],
    }

    let result = solve(n, &ab);
    writeln!(writer, "{}", result).unwrap();
    writer.flush().unwrap();
}
