use std::io::{BufRead, stdin};

fn decode_triplet(s: &str) -> (i16, i16, i16) {
    let parts: Vec<i16> = s.split(',').map(|x| x.parse().unwrap()).collect();
    (parts[0], parts[1], parts[2])
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();

    let triplests: Vec<(i16, i16, i16)> = lines
        .into_iter()
        .map(|line| decode_triplet(&line))
        .collect();

    eprintln!("{:?}", triplests);
}
