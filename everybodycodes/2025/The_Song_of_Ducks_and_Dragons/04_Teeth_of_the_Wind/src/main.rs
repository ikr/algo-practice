use num_rational::Rational64 as Ra;
use std::io::{BufRead, stdin};

#[derive(Clone, Copy)]
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
            (El::Tan(x), El::Tan(y)) => acc * Ra::new(x, y),
            (El::Tan(x), El::Ctr(a, _)) => acc * Ra::new(x, a),
            (El::Ctr(_, b), El::Tan(x)) => acc * Ra::new(b, x),
            (El::Ctr(_, b), El::Ctr(c, _)) => acc * Ra::new(b, c),
        });

    let result = Ra::from_integer(100) * mm;
    eprintln!("{}", result.numer() / result.denom());
}
