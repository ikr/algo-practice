use num_rational::Rational64 as Ra;
use std::io::{BufRead, stdin};

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let xs: Vec<i64> = lines.into_iter().map(|s| s.parse().unwrap()).collect();
    let ms: Vec<Ra> = xs.windows(2).map(|xy| Ra::new(xy[0], xy[1])).collect();
    let mm: Ra = ms.into_iter().fold(Ra::new(1, 1), |acc, m| acc * m);
    let result = Ra::from_integer(2025) * mm;
    eprintln!("{}", result.numer() / result.denom());
}
