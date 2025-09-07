use std::io::{BufRead, stdin};

fn extract_faces(input_line: &str) -> Vec<i32> {
    let csv = input_line.split(['[', ']']).nth(1).unwrap();
    csv.split(',').map(|s| s.parse().unwrap()).collect()
}

fn extract_seed(input_line: &str) -> i32 {
    input_line.split('=').last().unwrap().parse().unwrap()
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    for line in lines {
        let xs = extract_faces(&line);
        let s = extract_seed(&line);
        eprintln!("{:?} {s}", xs);
    }
}
