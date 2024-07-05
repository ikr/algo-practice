use std::io::{self, BufRead};

fn wrap_area(xs: [i32; 3]) -> i32 {
    let [l, w, h] = xs;
    3 * l * w + 2 * w * h + 2 * h * l
}

fn ribbon_length(xs: [i32; 3]) -> i32 {
    let [l, w, h] = xs;
    2 * l + 2 * w + l * w * h
}

fn parse_tri(src: &str) -> [i32; 3] {
    let mut xs = src
        .split('x')
        .map(|s| s.parse::<i32>().unwrap())
        .collect::<Vec<_>>();
    xs.sort();
    xs.try_into().unwrap()
}

fn main() {
    let xss: Vec<[i32; 3]> = io::stdin()
        .lock()
        .lines()
        .map(|line| parse_tri(&line.unwrap()))
        .collect();

    let result1 = xss.iter().fold(0, |acc, xs| acc + wrap_area(*xs));
    println!("{}", result1);

    let result2 = xss.into_iter().fold(0, |acc, xs| acc + ribbon_length(xs));
    println!("{}", result2);
}
