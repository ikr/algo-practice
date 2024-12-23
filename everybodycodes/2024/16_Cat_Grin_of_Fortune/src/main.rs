use std::io::{self, BufRead};

use itertools::Itertools;

fn transpose<T>(grid: Vec<Vec<T>>) -> Vec<Vec<T>> {
    assert!(!grid.is_empty());
    let h = grid[0].len();
    let mut iters: Vec<_> = grid.into_iter().map(|n| n.into_iter()).collect();
    (0..h)
        .map(|_| {
            iters
                .iter_mut()
                .map(|n| n.next().unwrap())
                .collect::<Vec<T>>()
        })
        .collect()
}

fn pad_right_to(n: usize, s: &str) -> String {
    if s.len() < n {
        s.to_string() + &" ".repeat(n - s.len())
    } else {
        s.to_string()
    }
}

fn coins_for(display: &[String]) -> usize {
    let xs: Vec<u8> = display
        .iter()
        .flat_map(|s| vec![s.as_bytes()[0], s.as_bytes()[2]])
        .collect();

    let fqs: Vec<usize> = xs.into_iter().counts().values().copied().collect();
    fqs.into_iter().filter(|&f| f >= 3).map(|f| f - 2).sum()
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().to_string())
        .collect();

    let steppings: Vec<usize> = lines[0].split(',').map(|s| s.parse().unwrap()).collect();

    let source_width = lines[2].len();
    let source_columns: Vec<Vec<u8>> = lines[2..]
        .iter()
        .map(|line| pad_right_to(source_width + 1, line).bytes().collect())
        .collect();

    let wheel_bands: Vec<String> = transpose(source_columns)
        .into_iter()
        .chunks(4)
        .into_iter()
        .map(|rows| {
            transpose(rows.into_iter().collect::<Vec<_>>())
                .into_iter()
                .map(|row| String::from_utf8(row).unwrap().trim_end().to_string())
                .collect()
        })
        .filter(|s: &String| !s.is_empty())
        .collect();

    let wheels: Vec<Vec<String>> = wheel_bands
        .into_iter()
        .map(|s| {
            s.chars()
                .chunks(3)
                .into_iter()
                .map(|xs| xs.collect())
                .collect()
        })
        .collect();

    assert_eq!(wheels.len(), steppings.len());

    let k_steps_gain = |shift: i8, k: usize| -> usize {
        let mut ps: Vec<usize> = wheels
            .iter()
            .map(|w| {
                let m = w.len();
                match shift {
                    -1 => m - 1,
                    0 => 0,
                    1 => 1,
                    _ => panic!("Unsupported shift of {}", shift),
                }
            })
            .collect();

        let mut total_coins: usize = 0;

        let current_display = |ps: &[usize]| -> Vec<String> {
            wheels
                .iter()
                .zip(ps.iter())
                .map(|(w, p)| w[*p].clone())
                .collect()
        };

        for _ in 1..=k {
            ps = ps
                .iter()
                .enumerate()
                .zip(steppings.iter())
                .map(|((i, p), step)| (p + step) % wheels[i].len())
                .collect();

            total_coins += coins_for(&current_display(&ps));
        }
        total_coins
    };

    let mut gains = [-1, 0, 1].map(|shift| k_steps_gain(shift, 2));
    gains.sort();
    println!("{:?}", gains);
}
