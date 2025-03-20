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
        .map(|s| decode_arg_in_line(s))
        .collect::<Vec<_>>()
        .try_into()
        .unwrap();

    let mut xs: Vec<i64> = lines[4..].iter().map(|s| s.parse().unwrap()).collect();
    xs.sort();
    let x0 = xs[xs.len() / 2];
    let result = x0.pow(c as u32) * b + a;
    println!("{}", result);
}
