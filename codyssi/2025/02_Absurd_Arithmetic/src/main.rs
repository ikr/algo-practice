use std::io::BufRead;

const HI: i64 = 15000000000000;

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

    let price_for_quality = |quality: i64| -> i64 { quality.pow(c as u32) * b + a };

    let xs: Vec<i64> = lines[4..].iter().map(|s| s.parse().unwrap()).collect();
    let x0: i64 = xs
        .into_iter()
        .filter(|&x| price_for_quality(x) <= HI)
        .max()
        .unwrap();
    println!("{}", x0);
}
