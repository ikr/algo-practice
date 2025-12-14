use std::io::Read;

fn isqrt(x: i64) -> Option<i64> {
    let fx = x as f64;
    let q = fx.sqrt().round();
    let i = q as i64;
    if i * i == x { Some(i) } else { None }
}

fn width_and_height(r: i64, b: i64) -> (i64, i64) {
    let d = (r + 4).pow(2) - 16 * r - 16 * b;
    let h = ((r + 4) + isqrt(d).unwrap()) / 4;
    let w = (r - 2 * h + 4) / 2;
    (w.max(h), w.min(h))
}

fn main() {
    let mut buf: String = String::new();
    std::io::stdin().read_to_string(&mut buf).unwrap();

    let [r, b] = buf
        .trim()
        .split_whitespace()
        .map(|s| s.parse::<i64>().unwrap())
        .collect::<Vec<_>>()
        .try_into()
        .unwrap();

    let (w, h) = width_and_height(r, b);
    assert!(w >= h);
    println!("{w} {h}");
}
