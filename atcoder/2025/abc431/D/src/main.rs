use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn max_happiness(params: &[(usize, u64, u64)]) -> u64 {
    let mut tab: Vec<u64> = vec![0; 500 * 500 + 1];
    let (w0, _, b0) = params[0];
    tab[w0] = b0;

    for &(w, h, b) in &params[1..] {
        let mut new_tab = tab.clone();
        new_tab[w] = new_tab[w].min(b);

        for (capacity, x) in tab.into_iter().enumerate() {
            if x != 0 {
                if capacity >= w {
                    new_tab[capacity - w] = new_tab[capacity - w].max(x + h);
                }

                if capacity + w < new_tab.len() {
                    new_tab[capacity + w] = new_tab[capacity + w].max(x + b);
                }
            }
        }

        tab = new_tab;
    }

    tab.into_iter().max().unwrap()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        mut params: [(usize, u64, u64); n],
    }

    let mut result = 0;
    for _ in 0..=n {
        params.rotate_right(1);
        result = result.max(max_happiness(&params));
    }

    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
