use regex::Regex;
use std::io::{self, BufRead};

const W: usize = 1001;
const H: usize = 1001;

struct Rectangle {
    id: u16,
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
    let re = Regex::new(r"^#(\d+) @ (\d+),(\d+): (\d+)x(\d+)$").unwrap();
    let caps = re.captures(src).unwrap();
    Rectangle {
        id: caps[1].parse().unwrap(),
        column: caps[2].parse().unwrap(),
        row: caps[3].parse().unwrap(),
        width: caps[4].parse().unwrap(),
        height: caps[5].parse().unwrap(),
    }
}

fn non_overlapping_rectangle_id(rectangles: Vec<Rectangle>, fs: [i32; H * W]) -> u16 {
    'outer: for r in &rectangles {
        for i in r.row..(r.row + r.height) {
            for j in r.column..(r.column + r.width) {
                if fs[i * W + j] != 1 {
                    continue 'outer;
                }
            }
        }
        return r.id;
    }
    0
}

fn main() {
    let rectangles = read_input()
        .iter()
        .map(|x| parse_rectangle(x))
        .collect::<Vec<_>>();

    let mut fs = [0; H * W];

    for r in &rectangles {
        for i in r.row..(r.row + r.height) {
            for j in r.column..(r.column + r.width) {
                fs[i * W + j] += 1;
            }
        }
    }

    println!("{}", non_overlapping_rectangle_id(rectangles, fs));
}
