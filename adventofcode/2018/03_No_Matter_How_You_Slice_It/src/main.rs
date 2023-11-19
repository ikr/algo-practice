use regex::Regex;
use std::io::{self, BufRead};

const W: usize = 1001;
const H: usize = 1001;

struct Rectangle {
    column: usize,
    row: usize,
    width: usize,
    height: usize,
}

fn read_input() -> Vec<String> {
    let mut xs = Vec::new();
    for line in io::stdin().lock().lines() {
        xs.push(String::from(line.unwrap().trim()));
    }
    xs
}

fn parse_rectangle(src: &str) -> Rectangle {
    let re = Regex::new(r"^#\d+ @ (\d+),(\d+): (\d+)x(\d+)$").unwrap();
    let caps = re.captures(src).unwrap();
    Rectangle {
        column: caps[1].parse().unwrap(),
        row: caps[2].parse().unwrap(),
        width: caps[3].parse().unwrap(),
        height: caps[4].parse().unwrap(),
    }
}

fn main() {
    let rectangles = read_input()
        .iter()
        .map(|x| parse_rectangle(x))
        .collect::<Vec<_>>();

    let mut fs = [0; H * W];

    for r in rectangles {
        for i in r.row..(r.row + r.height) {
            for j in r.column..(r.column + r.width) {
                fs[i * W + j] += 1;
            }
        }
    }

    let result = fs.iter().filter(|x| **x > 1).count();
    println!("{}", result);
}
