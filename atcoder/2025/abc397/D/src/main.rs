use proconio::input;
use std::io::{self, BufWriter, Write};

const MIO: i128 = 1_000_000;

fn isqrt(x: i128) -> Option<i128> {
    let fx = x as f64;
    let q = fx.sqrt().round();
    let i = q as i128;
    if i * i == x { Some(i) } else { None }
}

fn find_y(n: i128, d: i128) -> Option<i128> {
    let discr: i128 = 9 * d.pow(4) - 12 * d * (d.pow(3) - n);
    if discr < 0 {
        return None;
    }

    let dd = isqrt(discr)?;
    let p = -3 * d * d + dd;
    if p <= 0 || p % (6 * d) != 0 {
        return None;
    }

    Some(p / 6 * d)
}

fn solve(n: i128) -> Option<(i128, i128)> {
    for d in 1..=MIO {
        if let Some(y) = find_y(n, d) {
            return Some((y + d, y));
        }
    }

    None
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: u64,
    }

    if let Some((x, y)) = solve(n as i128) {
        writeln!(writer, "{} {}", x, y).unwrap();
    } else {
        writeln!(writer, "-1").unwrap();
    }
    writer.flush().unwrap();
}
