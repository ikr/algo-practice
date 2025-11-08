use itertools::Itertools;
use std::io::Read;

#[derive(Clone, Copy)]
enum El {
    Single(i32),
    WithL(i32),
    WithR(i32),
    WithLR(i32),
}

impl El {
    fn center(self) -> i32 {
        match self {
            El::Single(x) => x,
            El::WithL(x) => x,
            El::WithR(x) => x,
            El::WithLR(x) => x,
        }
    }

    fn accommodate(self, x: i32) -> Option<Self> {
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

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).unwrap();
    let isep = buf.bytes().position(|x| x == b':').unwrap();

    let xs: Vec<i32> = buf[isep + 1..]
        .trim()
        .split(',')
        .map(|s| s.parse::<i32>().unwrap())
        .collect();

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

    println!("{}", result.into_iter().map(|el| el.center()).join(""));
}
