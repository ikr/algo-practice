use std::io::{BufRead, stdin};

fn first(s: &str) -> char {
    s.chars().next().unwrap()
}

fn decode_rule(s: &str) -> Vec<(char, char)> {
    let parts: Vec<_> = s.split(" > ").collect();
    let a: char = first(parts[0]);
    parts[1].split(',').map(|x| (a, first(x))).collect()
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let names: Vec<String> = lines[0].split(',').map(|x| x.to_string()).collect();
    let ps: Vec<(char, char)> = lines[2..].iter().flat_map(|x| decode_rule(x)).collect();

    let result: usize = names
        .into_iter()
        .enumerate()
        .filter_map(|(i, s)| {
            if s.chars()
                .collect::<Vec<_>>()
                .windows(2)
                .all(|xy| ps.contains(&(xy[0], xy[1])))
            {
                Some(i + 1)
            } else {
                None
            }
        })
        .sum();

    println!("{result}");
}
