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

fn can_pass_through(depth_ranges: &[(i32, i32)], delay: i32) -> bool {
    for (d, r) in depth_ranges {
        if (delay + d) % (2 * (r - 1)) == 0 {
            return false;
        }
    }
    true
}

fn solve_part_2(depth_ranges: &[(i32, i32)]) -> i32 {
    for i in 0..1_000_000_000 {
        if can_pass_through(depth_ranges, i) {
            return i;
        }
    }
    -1
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
