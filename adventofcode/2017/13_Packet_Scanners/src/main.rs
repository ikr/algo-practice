use std::io::{self, BufRead};

fn parse_input_line(src: &str) -> (i32, i32) {
    let parts: Vec<String> = src.split(": ").map(|x| x.to_string()).collect();
    let a = parts[0].parse().unwrap();
    let b = parts[1].parse().unwrap();
    (a, b)
}

fn solve_part_1(depth_ranges: &[(i32, i32)]) -> i32 {
    let mut result = 0;
    for (d, r) in depth_ranges {
        if d % (2 * (r - 1)) == 0 {
            result += d * r;
        }
    }
    result
}

fn solve_part_2(depth_ranges: &[(i32, i32)]) -> i32 {
    0
}

fn main() {
    let depth_ranges: Vec<(i32, i32)> = io::stdin()
        .lock()
        .lines()
        .map(|l| l.unwrap())
        .map(|l| parse_input_line(&l))
        .collect();

    println!("{}", solve_part_1(&depth_ranges));
    println!("{}", solve_part_2(&depth_ranges));
}
