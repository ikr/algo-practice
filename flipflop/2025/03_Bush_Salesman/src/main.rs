use itertools::Itertools;
use std::io::{BufRead, stdin};

#[derive(Clone, Copy, Debug, PartialEq)]
enum Label {
    R,
    G,
    B,
    Sp,
}

impl Label {
    fn from_dominant_index(i: usize) -> Self {
        match i {
            0 => Self::R,
            1 => Self::G,
            2 => Self::B,
            _ => unreachable!(),
        }
    }

    fn values_with_other_indices(xs: [u8; 3], i0: usize) -> [u8; 2] {
        xs.into_iter()
            .enumerate()
            .filter_map(|(i, x)| if i == i0 { None } else { Some(x) })
            .collect::<Vec<_>>()
            .try_into()
            .unwrap()
    }

    fn from_rgb(rgb: (u8, u8, u8)) -> Self {
        let xs: [u8; 3] = rgb.into();

        if xs.iter().tuple_combinations().any(|(a, b)| a == b) {
            Self::Sp
        } else {
            Self::from_dominant_index(
                xs.iter()
                    .enumerate()
                    .position(|(i, &x)| {
                        let ys = Self::values_with_other_indices(xs, i);
                        ys.into_iter().all(|y| y < x)
                    })
                    .unwrap(),
            )
        }
    }
}

fn decode_line(s: &str) -> (u8, u8, u8) {
    s.split(',')
        .map(|sub| sub.parse().unwrap())
        .collect_tuple()
        .unwrap()
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let rgbs: Vec<_> = lines.into_iter().map(|s| decode_line(&s)).collect();
    let labels: Vec<Label> = rgbs.into_iter().map(Label::from_rgb).collect();
    let result = labels.into_iter().filter(|&l| l == Label::G).count();
    println!("{result}");
}
