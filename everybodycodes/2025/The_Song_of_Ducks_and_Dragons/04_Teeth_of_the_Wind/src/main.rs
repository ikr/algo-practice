use num_rational::Rational64 as Ra;
use std::io::{BufRead, stdin};

#[derive(Clone, Copy, Debug)]
enum El {
    Tan(i64),
    Ctr(i64, i64),
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let chain: Vec<El> = lines
        .into_iter()
        .map(|s| {
            if s.contains('|') {
                let parts: Vec<_> = s.split('|').collect();
                El::Ctr(parts[0].parse().unwrap(), parts[1].parse().unwrap())
            } else {
                El::Tan(s.parse().unwrap())
            }
        })
        .collect();

    let mm: Ra = chain
        .windows(2)
        .fold(Ra::from_integer(1), |acc, xy| match (xy[0], xy[1]) {
            (El::Tan(x), El::Tan(y)) => Ra::new(x, y),
        });

    // let xs: Vec<i64> = lines.into_iter().map(|s| s.parse().unwrap()).collect();
    // let ms: Vec<Ra> = xs.windows(2).map(|xy| Ra::new(xy[0], xy[1])).collect();
    // let mm: Ra = ms.into_iter().fold(Ra::new(1, 1), |acc, m| acc * m);

    let result = Ra::from_integer(100) * mm;
    eprintln!(
        "{}",
        (*result.numer() as u64).div_ceil(*result.denom() as u64)
    );
}
