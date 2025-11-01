use itertools::Itertools;
use proconio::input;
use proconio::marker::Bytes;
use std::io::{BufWriter, Write, stdout};

fn is_violating(xs: &[u8], aa: usize, bb: usize) -> bool {
    let n = xs.len();
    let a = xs.iter().filter(|&&x| x == b'a').count();
    let b = n - a;
    if a >= aa { b < bb } else { false }
}

fn brute_num_violating_intervals(xs: Vec<u8>, aa: usize, bb: usize) -> usize {
    let n = xs.len();
    (0..n)
        .combinations_with_replacement(2)
        .filter(|ij| is_violating(&xs[ij[0]..=ij[1]], aa, bb))
        .count()
}

fn num_violating_intervals(xs: Vec<u8>, aa: usize, bb: usize) -> usize {
    let n = xs.len();
    let mut i: usize = 0;
    let mut j: usize = 0;
    let mut a: usize = if xs[0] == b'a' { 1 } else { 0 };
    let mut b: usize = if xs[0] == b'b' { 1 } else { 0 };
    let mut result = 0;

    if a >= aa && b < bb {
        result += 1;
    }

    while i < n - 1 {
        assert!(i <= j);

        if j == n - 1 {
            match xs[i] {
                b'a' => a -= 1,
                b'b' => b -= 1,
                _ => unreachable!(),
            }
            i += 1;
        } else {
            if a < aa {
                j += 1;

                if j < n {
                    match xs[j] {
                        b'a' => a += 1,
                        b'b' => b += 1,
                        _ => unreachable!(),
                    }
                }
            } else {
                if b >= bb {
                    match xs[i] {
                        b'a' => a -= 1,
                        b'b' => b -= 1,
                        _ => unreachable!(),
                    }
                    i += 1;
                    j = j.max(i);
                } else {
                    if a > aa {
                        match xs[i] {
                            b'a' => a -= 1,
                            b'b' => b -= 1,
                            _ => unreachable!(),
                        }
                        i += 1;
                        j = j.max(i);
                    } else {
                        j += 1;

                        if j < n {
                            match xs[j] {
                                b'a' => a += 1,
                                b'b' => b += 1,
                                _ => unreachable!(),
                            }
                        }
                    }
                }
            }
        }

        if a >= aa && b < bb {
            //eprintln!("{:?}", (i, j));
            result += 1;
        }
    }

    result
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        aa: usize,
        bb: usize,
        xs: Bytes,
    }
    assert_eq!(xs.len(), n);

    let result = num_violating_intervals(xs, aa, bb);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_against_brute() {
        for (xs, aa, bb) in vec![
            ("a", 1, 1),
            ("abbaaabaaba", 4, 2),
            ("bbbbbbbb", 1, 2),
            ("aabb", 2, 1),
            (
                "aaabababaaaabababbababbbaaaaaaabbabababababaaaabbbaaaaa",
                5,
                3,
            ),
        ] {
            let expected = brute_num_violating_intervals(xs.as_bytes().to_vec(), aa, bb);
            let actual = num_violating_intervals(xs.as_bytes().to_vec(), aa, bb);
            assert_eq!(actual, expected, "on {xs} {aa} {bb}");
        }
    }
}
