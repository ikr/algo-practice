use ac_library::ModInt998244353 as Mint;
use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn megasum(mut aa: Vec<i32>, bb: Vec<i32>) -> i32 {
    aa.sort();
    let n = aa.len();

    let mut tab: Vec<Mint> = vec![Mint::new(0); n];
    for i in 1..n {
        tab[i] = tab[i - 1] + Mint::new(i) * (aa[i] - aa[i - 1]);
    }

    let mut bat: Vec<Mint> = vec![Mint::new(0); n];
    for i in (0..n - 1).rev() {
        bat[i] = bat[i + 1] + Mint::new(n - 1 - i) * (aa[i + 1] - aa[i]);
    }

    let mut result: Mint = Mint::new(0);

    for b in bb {
        let i0 = aa.partition_point(|&a| a <= b);
        let lhs = i0;
        let rhs = n - lhs;

        if aa[0] <= b {
            result += Mint::new(b - aa[i0 - 1]) * Mint::new(lhs) + tab[i0 - 1];
        }

        if b <= aa[n - 1] {
            result += if i0 < n {
                Mint::new(aa[i0] - b)
            } else {
                Mint::new(0)
            } * Mint::new(rhs)
                + if i0 < n { bat[i0] } else { Mint::new(0) };
        }
    }

    result.val() as i32
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        m: usize,
        aa: [i32; n],
        bb: [i32; m],
    }

    let result = megasum(aa, bb);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
