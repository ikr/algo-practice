use proconio::{derive_readable, input};
use std::io::{BufWriter, Write, stdout};

#[derive_readable]
#[derive(Clone, Copy)]
struct Present {
    p: usize,
    a: usize,
    b: usize,
}

// T[i][j] is the final mood given that before opening the present i the mood was j
fn sequential_moods_table(presents: &[Present]) -> Vec<Vec<usize>> {
    let n = presents.len();
    let mut result = vec![vec![usize::MAX; 1001]; n];

    let tail: Present = presents[n - 1];
    for (j, x) in result[n - 1].iter_mut().enumerate() {
        *x = if j <= tail.p {
            j + tail.a
        } else {
            j.saturating_sub(tail.b)
        }
    }

    for i in (0..n - 1).rev() {
        for j in 0..=1000 {
            result[i][j] = if j <= presents[i].p {
                result[i + 1][j + presents[i].a]
            } else {
                result[i + 1][j.saturating_sub(presents[i].b)]
            };
        }
    }

    result
}

fn prefix_subs_of_mood_drops(presents: &[Present]) -> Vec<usize> {
    presents
        .iter()
        .scan(0usize, |s, pr| {
            *s += pr.b;
            Some(*s)
        })
        .collect()
}

fn final_moods(presents: Vec<Present>, xs: Vec<usize>) -> Vec<usize> {
    let n = presents.len();
    let dp = sequential_moods_table(&presents);
    let ss = prefix_subs_of_mood_drops(&presents);

    xs.into_iter()
        .map(|x0| {
            if x0 <= 1000 {
                dp[0][x0]
            } else {
                let i0 = ss.partition_point(|&s| x0.saturating_sub(s) > 1000);
                if i0 >= n - 1 {
                    x0.saturating_sub(ss[n - 1])
                } else {
                    dp[i0 + 1][x0.saturating_sub(ss[i0])]
                }
            }
        })
        .collect()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        presents: [Present; n],
        q: usize,
        xs: [usize; q],
    }

    let results = final_moods(presents, xs);
    for r in results {
        writeln!(writer, "{r}").unwrap();
    }
    writer.flush().unwrap();
}
