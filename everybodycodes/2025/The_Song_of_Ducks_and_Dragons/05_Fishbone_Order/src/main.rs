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

    let mut result: Vec<El> = vec![];
    for x in xs {
        let mut patched = false;

        for el in &mut result {
            match *el {
                El::Single(y) => {
                    if x < y {
                        *el = El::WithL(y);
                        patched = true;
                        break;
                    } else if x > y {
                        *el = El::WithR(y);
                        patched = true;
                        break;
                    }
                }
                El::WithL(y) => {
                    if x > y {
                        *el = El::WithLR(y);
                        patched = true;
                        break;
                    }
                }
                El::WithR(y) => {
                    if x < y {
                        *el = El::WithLR(y);
                        patched = true;
                        break;
                    }
                }
                El::WithLR(_) => {}
            }
        }

        if !patched {
            result.push(El::Single(x));
        }
    }

    println!("{}", result.into_iter().map(|el| el.center()).join(""));
}
