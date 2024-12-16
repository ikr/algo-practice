use std::io::{self, BufRead};

use itertools::Itertools;
use num_integer::lcm;

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

fn coins_for(display: &[String]) -> u64 {
    let xs: Vec<u8> = display
        .iter()
        .flat_map(|s| vec![s.as_bytes()[0], s.as_bytes()[2]])
        .collect();

    let fqs: Vec<usize> = xs.into_iter().counts().values().copied().collect();

    fqs.into_iter()
        .filter(|&f| f >= 3)
        .map(|f| f as u64 - 2)
        .sum()
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
    eprintln!("wheel_bands:\n{:?}", wheel_bands);

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
    eprintln!("wheels:\n{:?}", wheels);
    eprintln!("steppings: {:?}", steppings);
    assert_eq!(wheels.len(), steppings.len());

    let common_perion: u64 = steppings.iter().fold(1, |acc, &p| lcm(acc, p as u64));
    eprintln!("common_period:{}", common_perion);

    let n = wheels.len();
    let mut ps = vec![0; n];
    for _ in 0..100 {
        ps = ps
            .iter()
            .enumerate()
            .zip(steppings.iter())
            .map(|((i, p), step)| (p + step) % wheels[i].len())
            .collect()
    }

    let result: String = wheels
        .iter()
        .zip(ps.iter())
        .map(|(w, p)| w[*p].clone())
        .join(" ");

    println!("{}", result);
}
