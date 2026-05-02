use ac_library::ModInt998244353 as Mint;
use proconio::input;
use proconio::marker::Bytes;
use std::io::{BufWriter, Write, stdout};

fn run_length_encoding(xs: Vec<u8>) -> Vec<(u8, usize)> {
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

fn num_substrings_for_length(length: usize) -> Mint {
    Mint::new(length * (length + 1) / 2)
}

fn num_good_substrings(xs: Vec<u8>) -> Mint {
    let mut l: usize = 0;
    let mut result = Mint::new(0);

    for (_, k) in run_length_encoding(xs) {
        assert_ne!(k, 0);
        l += 1;

        if k != 1 {
            result += num_substrings_for_length(l);
            result += k - 2;
            l = 1;
        }
    }

    result += num_substrings_for_length(l);
    result
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        xs: Bytes,
    }

    let result = num_good_substrings(xs);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
