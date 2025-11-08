use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn max_happiness(params: &[(usize, u64, u64)]) -> u64 {
    let mut tab: Vec<(usize, u64)> = vec![(0, 0); 25001];
    let (w0, _, b0) = params[0];
    tab[w0] = (0, b0);

    for &(w, h, b) in &params[1..] {
        let mut new_tab = tab.clone();

        for (wb, (wh, x0)) in tab.into_iter().enumerate() {
            if wh + w <= wb {
                let (cur_wb, cur_x) = new_tab[wb];
                new_tab[wb] = todo!();
            }
        }

        tab = new_tab;
    }

    tab.into_iter().map(|(_, h)| h).max().unwrap()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        params: [(usize, u64, u64); n],
    }

    let result = max_happiness(&params);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
