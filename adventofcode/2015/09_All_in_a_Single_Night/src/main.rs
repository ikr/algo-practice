use std::io::{self, BufRead};

fn parse_line_parts(src: &str) -> (String, i32) {
    let [a, b] = src.split(" = ").collect::<Vec<_>>()[..] else {
        panic!("Invalid line {}", src)
    };
    (a.to_owned(), b.parse().unwrap())
}

fn parse_cities(src: &str) -> (String, String) {
    let [a, b] = src.split(" to ").collect::<Vec<_>>()[..] else {
        panic!("Invalid cities pair {}", src)
    };
    (a.to_owned(), b.to_owned())
}

fn parse_line(src: &str) -> (String, String, i32) {
    let (ab, distance) = parse_line_parts(src);
    let (a, b) = parse_cities(&ab);
    (a, b, distance)
}

fn index_of(haystack: &[String], needle: &str) -> usize {
    haystack.iter().position(|s| s == needle).unwrap()
}

fn main() {
    let facts: Vec<_> = io::stdin()
        .lock()
        .lines()
        .map(|line| parse_line(&line.unwrap()))
        .collect();

    eprintln!("{:?}", facts);
}
