use std::io::BufRead;

fn main() {
    let lines: Vec<String> = std::io::stdin()
        .lock()
        .lines()
        .map(|s| s.unwrap())
        .collect();

    let initial: i32 = lines[0].parse().unwrap();
    let change_abses: Vec<i32> = lines[1..lines.len() - 1]
        .iter()
        .map(|s| s.parse().unwrap())
        .collect();
    let signs: Vec<i32> = lines[lines.len() - 1]
        .chars()
        .map(|c| if c == '-' { -1 } else { 1 })
        .collect();

    let result: i32 = signs
        .into_iter()
        .rev()
        .zip(change_abses)
        .map(|(sign, x)| sign * x)
        .fold(initial, |acc, x| acc + x);

    println!("{}", result);
}
