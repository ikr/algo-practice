use itertools::{Itertools, MinMaxResult};
use std::io::BufRead;

#[derive(Clone, Copy)]
enum El {
    Single(u8),
    WithL(u8),
    WithR(u8),
    WithLR(u8),
}

impl El {
    fn center(self) -> u8 {
        match self {
            El::Single(x) => x,
            El::WithL(x) => x,
            El::WithR(x) => x,
            El::WithLR(x) => x,
        }
    }

    fn accommodate(self, x: u8) -> Option<Self> {
        match self {
            El::Single(y) => {
                if x < y {
                    Some(El::WithL(y))
                } else if x > y {
                    Some(El::WithR(y))
                } else {
                    None
                }
            }
            El::WithL(y) => {
                if x > y {
                    Some(El::WithLR(y))
                } else {
                    None
                }
            }
            El::WithR(y) => {
                if x < y {
                    Some(El::WithLR(y))
                } else {
                    None
                }
            }
            El::WithLR(_) => None,
        }
    }
}

fn fishbone(xs: Vec<u8>) -> Vec<El> {
    let mut result: Vec<El> = vec![];

    for x in xs {
        if let Some((i, new_el)) = result
            .iter()
            .enumerate()
            .filter_map(|(j, el)| el.accommodate(x).map(|new_el| (j, new_el)))
            .next()
        {
            result[i] = new_el;
        } else {
            result.push(El::Single(x));
        }
    }

    result
}

fn quality(xs: Vec<u8>) -> u64 {
    fishbone(xs)
        .into_iter()
        .map(|el| el.center())
        .join("")
        .parse()
        .unwrap()
}

fn parse_line(s: String) -> Vec<u8> {
    let isep = s.find(':').unwrap();

    s[isep + 1..]
        .split(',')
        .map(|s| s.parse::<u8>().unwrap())
        .collect()
}

fn main() {
    let xss: Vec<Vec<u8>> = std::io::stdin()
        .lock()
        .lines()
        .map(|line| parse_line(line.unwrap()))
        .collect();

    let qs: Vec<_> = xss.into_iter().map(quality).collect();
    match qs.into_iter().minmax() {
        MinMaxResult::MinMax(lo, hi) => println!("{}", hi - lo),
        _ => unreachable!(),
    }
}
