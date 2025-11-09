use proconio::input;
use std::io::{BufWriter, Write, stdout};

#[derive(Clone, Copy)]
struct Part {
    w: usize,
    h: u64,
    b: u64,
}

fn max_happiness(parts: Vec<Part>) -> u64 {
    let (total_weight, total_body_happiness) =
        parts.iter().fold((0, 0), |(w, b), p| (w + p.w, b + p.b));

    // tab[i] is the current head happiness
    let mut tab = vec![0; total_weight / 2 + 1];
    tab[0] = total_body_happiness;

    for p in parts {
        let n = tab.len();
        let mut new_tab = tab.clone();

        for (w0, h0) in tab.into_iter().enumerate() {
            if w0 + p.w < n && h0 != 0 {
                new_tab[w0 + p.w] = new_tab[w0 + p.w].max(h0 + p.h - p.b);
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
        params: [(usize, u64, u64); n],
    }

    let result = max_happiness(
        params
            .into_iter()
            .map(|(w, h, b)| Part { w, h, b })
            .collect(),
    );
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
