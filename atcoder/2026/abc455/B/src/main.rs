use proconio::input;
use proconio::marker::Bytes;
use std::io::{BufWriter, Write, stdout};

fn is_point_symmetric(xss: &[Vec<u8>], h1: usize, h2: usize, w1: usize, w2: usize) -> bool {
    for i in h1..=h2 {
        for j in w1..=w2 {
            if xss[i][j] != xss[h1 + h2 - i][w1 + w2 - j] {
                return false;
            }
        }
    }

    true
}

fn num_good_subgrids(xss: Vec<Vec<u8>>) -> usize {
    let h = xss.len();
    let w = xss[0].len();

    let mut result = 0;

    for h1 in 0..h {
        for h2 in h1..h {
            for w1 in 0..w {
                for w2 in w1..w {
                    if is_point_symmetric(&xss, h1, h2, w1, w2) {
                        result += 1;
                    }
                }
            }
        }
    }

    result
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        h: usize,
        w: usize,
        xss: [Bytes; h],
    }
    assert_eq!(xss[0].len(), w);

    let result = num_good_subgrids(xss);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
