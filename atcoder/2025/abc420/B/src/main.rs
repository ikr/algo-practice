use proconio::input;
use proconio::marker::Bytes;
use std::io::{BufWriter, Write, stdout};

fn transpose<T>(grid: Vec<Vec<T>>) -> Vec<Vec<T>> {
    assert!(!grid.is_empty());
    let h = grid[0].len();
    let mut iters: Vec<_> = grid.into_iter().map(|n| n.into_iter()).collect();
    (0..h)
        .map(|_| {
            iters
                .iter_mut()
                .map(|n| n.next().unwrap())
                .collect::<Vec<T>>()
        })
        .collect()
}

enum VoteMinority {
    Zero,
    One,
    Both,
}

fn minority_report(xs: Vec<usize>) -> VoteMinority {
    let m = xs.len();
    let ones = xs.into_iter().filter(|&x| x == 1).count();
    let zeros = m - ones;

    if ones < zeros {
        VoteMinority::One
    } else if zeros < ones {
        VoteMinority::Zero
    } else {
        assert_eq!(ones, zeros);
        VoteMinority::Both
    }
}

fn top_score_indices(xss: Vec<Vec<usize>>) -> Vec<usize> {
    let mrs: Vec<VoteMinority> = transpose(xss.clone())
        .into_iter()
        .map(|ys| minority_report(ys))
        .collect();

    let score = |xs: Vec<usize>| -> usize {
        xs.into_iter()
            .enumerate()
            .map(|(i, x)| match mrs[i] {
                VoteMinority::One => {
                    if x == 1 {
                        1
                    } else {
                        0
                    }
                }
                VoteMinority::Zero => {
                    if x == 0 {
                        1
                    } else {
                        0
                    }
                }
                VoteMinority::Both => 1,
            })
            .sum()
    };

    let scores: Vec<usize> = xss.into_iter().map(score).collect();
    let hi = *scores.iter().max().unwrap();

    scores
        .into_iter()
        .enumerate()
        .filter_map(|(i, x)| if x == hi { Some(i) } else { None })
        .collect()
}

fn represent_result(indices: Vec<usize>) -> String {
    indices
        .into_iter()
        .map(|i| (i + 1).to_string())
        .collect::<Vec<_>>()
        .join(" ")
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        _: usize,
        ss: [Bytes; n],
    }

    let xss: Vec<Vec<usize>> = ss
        .into_iter()
        .map(|bs| bs.into_iter().map(|x| (x - b'0') as usize).collect())
        .collect();

    let result = represent_result(top_score_indices(xss));
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
