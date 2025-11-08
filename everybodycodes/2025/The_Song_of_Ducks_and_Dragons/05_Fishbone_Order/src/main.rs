use itertools::Itertools;
use std::io::BufRead;

#[derive(Clone, Copy)]
enum El {
    Single(u8),
    WithL { lhs: u8, value: u8 },
    WithR { value: u8, rhs: u8 },
    WithLR { lhs: u8, value: u8, rhs: u8 },
}

impl El {
    fn center(self) -> u8 {
        match self {
            El::Single(x) => x,
            El::WithL { lhs: _, value } => value,
            El::WithR { value, rhs: _ } => value,
            El::WithLR {
                lhs: _,
                value,
                rhs: _,
            } => value,
        }
    }

    fn values(self) -> Vec<u8> {
        match self {
            El::Single(x) => vec![x],
            El::WithL { lhs, value } => vec![lhs, value],
            El::WithR { value, rhs } => vec![value, rhs],
            El::WithLR { lhs, value, rhs } => vec![lhs, value, rhs],
        }
    }

    fn seq_num(self) -> u16 {
        self.values().into_iter().join("").parse().unwrap()
    }

    fn accommodate(self, x: u8) -> Option<Self> {
        match self {
            El::Single(value) => {
                if x < value {
                    Some(El::WithL { lhs: x, value })
                } else if x > value {
                    Some(El::WithR { value, rhs: x })
                } else {
                    None
                }
            }
            El::WithL { lhs, value } => {
                if x > value {
                    Some(El::WithLR { lhs, value, rhs: x })
                } else {
                    None
                }
            }
            El::WithR { value, rhs } => {
                if x < value {
                    Some(El::WithLR { lhs: x, value, rhs })
                } else {
                    None
                }
            }
            El::WithLR {
                lhs: _,
                value: _,
                rhs: _,
            } => None,
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

fn quality(xs: &[El]) -> u64 {
    xs.iter().map(|el| el.center()).join("").parse().unwrap()
}

fn level_seq_nums(xs: &[El]) -> Vec<u16> {
    xs.iter().map(|el| el.seq_num()).collect()
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

    let mut fbs: Vec<(usize, Vec<El>)> = xss
        .into_iter()
        .enumerate()
        .map(|(i, xs)| (i + 1, fishbone(xs)))
        .collect();

    fbs.sort_by(|(i, fb_a), (j, fb_b)| {
        let qa = quality(fb_a);
        let qb = quality(fb_b);

        if qa == qb {
            let sna = level_seq_nums(fb_a);
            let snb = level_seq_nums(fb_b);

            if sna == snb {
                i.cmp(j).reverse()
            } else {
                sna.cmp(&snb).reverse()
            }
        } else {
            qa.cmp(&qb).reverse()
        }
    });

    let checksum: usize = fbs
        .into_iter()
        .map(|(id, _)| id)
        .enumerate()
        .map(|(i, id)| (i + 1) * id)
        .sum();

    println!("{checksum}");
}
