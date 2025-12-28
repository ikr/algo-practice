use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn run_length_encoding(xs: Vec<u32>) -> Vec<(u32, usize)> {
    xs.into_iter().fold(vec![], |mut acc, x| {
        if let Some(e) = acc.last_mut()
            && e.0 == x
        {
            e.1 += 1;
        } else {
            acc.push((x, 1))
        }
        acc
    })
}

fn min_terminal_length(xs: Vec<u32>) -> usize {
    let rle = run_length_encoding(xs).into_iter().filter_map(|(x, k)| {
        if k.is_multiple_of(4) {
            None
        } else {
            Some((x, k % 4))
        }
    });

    let mut st: Vec<(u32, usize)> = vec![];

    for (x0, mut k0) in rle {
        while let Some(&(x, k)) = st.last()
            && x0 == x
        {
            st.pop();
            k0 += k;
            k0 %= 4;
        }

        if k0 != 0 {
            st.push((x0, k0));
        }
    }

    st.into_iter().map(|(_, k)| k).sum()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        xs: [u32; n],
    }

    let result = min_terminal_length(xs);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
