use std::io::Read;

fn width_and_height(r: i64, b: i64) -> (i64, i64) {
    let d = (r + 2).pow(2) - 16 * r - 16 * b;
    let h = ((r + 2) + d.isqrt()) / 4;
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
