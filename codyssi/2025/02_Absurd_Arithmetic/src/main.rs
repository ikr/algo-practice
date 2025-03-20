use std::io::BufRead;

fn decode_arg_in_line(s: &str) -> i64 {
    s.split_ascii_whitespace().last().unwrap().parse().unwrap()
}

fn main() {
    let lines: Vec<String> = std::io::stdin()
        .lock()
        .lines()
        .map(|s| s.unwrap())
        .collect();

    let [a, b, c] = lines[..3]
        .iter()
        .map(|s| decode_arg_in_line(&s))
        .collect::<Vec<_>>()
        .try_into()
        .unwrap();

    eprintln!("{} {} {}", a, b, c);
}
