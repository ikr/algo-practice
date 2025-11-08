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

    let mut result: Vec<i32> = vec![];
    let mut cur: El = El::Single(xs[0]);

    for &x in &xs[1..] {
        match cur {
            El::Single(y) => {
                if x <= y {
                    cur = El::WithL(y);
                } else {
                    cur = El::WithR(y);
                }
            }
            El::WithL(y) => {
                if x <= y {
                    result.push(x);
                    cur = El::Single(y);
                } else {
                    cur = El::WithLR(y);
                }
            }
            El::WithR(y) => {
                if x <= y {
                    cur = El::WithLR(y);
                } else {
                    result.push(x);
                    cur = El::Single(y);
                }
            }
            El::WithLR(y) => {
                result.push(x);
                cur = El::Single(y);
            }
        }
    }
    result.push(cur.center());

    println!("{}", result.iter().join(""))
}
