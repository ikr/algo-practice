use std::io::{self, BufRead};

fn parse_line(s: &str) -> (String, Vec<i32>) {
    let parts: Vec<&str> = s.split(":").collect();
    let lhs = parts[0].to_string();
    let rhs = parts[1]
        .split(",")
        .map(|s| match s {
            "-" => -1,
            "=" => 0,
            "+" => 1,
            _ => panic!("Unknown op {}", s),
        })
        .collect();
    (lhs, rhs)
}

fn total_essence_gathered(track: &[i32], loops: usize, initial_essence: i32, xs: &[i32]) -> i32 {
    let mut t: usize = 0;
    let mut cur = initial_essence;
    let mut result = 0;
    let m = xs.len();

    for _ in 0..loops {
        for terrain in track {
            match (terrain, xs[t % m]) {
                (-1, _) => cur -= 1,
                (0, x) => cur += x,
                (1, _) => cur += 1,
                _ => panic!("Unknown terrain {} or op {}", terrain, xs[t % m]),
            }
            result += cur;
            t += 1;
        }
    }

    result
}

fn reversed(s: &str) -> String {
    s.chars().rev().collect()
}

fn track_src_a() -> String {
    "+===".to_string() + "+" + &reversed("=+=-+") + "-S"
}

fn track_src_1() -> String {
    "-=++=-==++=++=-=+=-=+=+=--=-=++=-==++=-+=-=+=-=+=+=++=-+==++=++=-=-=--".to_string()
        + "-=++==-"
        + &reversed("--==++++==+=+++-=+=-=+=-+-=+-=+-=+=-=+=--=+++=++=+++==++==--=+=++==+++-")
        + "-=+=+=-S"
}

fn track_from(track_src: &str) -> Vec<i32> {
    track_src
        .chars()
        .map(|c| match c {
            '-' => -1,
            '=' => 0,
            '+' => 1,
            'S' => 0,
            _ => panic!("Unknown char {}", c),
        })
        .collect()
}

fn main() {
    let mut lines = io::stdin()
        .lock()
        .lines()
        .map(|line| parse_line(&line.unwrap()))
        .collect::<Vec<_>>();

    lines.sort_by_key(|(_, xs)| -total_essence_gathered(&track_from(&track_src_1()), 10, 10, xs));
    let result = lines
        .into_iter()
        .map(|(s, _)| s)
        .collect::<Vec<_>>()
        .join("");
    println!("{}", result);
}
