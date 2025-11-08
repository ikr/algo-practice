use itertools::Itertools;
use std::io::Read;

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

fn quality(xs: Vec<u8>) -> u64 {
    let mut result: Vec<El> = vec![];

    for x in xs {
        if let Some((i, new_el)) = result
            .iter()
            .enumerate()
            .filter_map(|(j, el)| {
                if let Some(new_el) = el.accommodate(x) {
                    Some((j, new_el))
                } else {
                    None
                }
            })
            .next()
        {
            result[i] = new_el;
        } else {
            result.push(El::Single(x));
        }
    }

    result
        .into_iter()
        .map(|el| el.center())
        .join("")
        .parse()
        .unwrap()
}

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).unwrap();
    let isep = buf.bytes().position(|x| x == b':').unwrap();

    let xs: Vec<u8> = buf[isep + 1..]
        .trim()
        .split(',')
        .map(|s| s.parse::<u8>().unwrap())
        .collect();

    println!("{}", quality(xs));
}
