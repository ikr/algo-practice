use std::io::BufRead;

fn join_into_int(ab: &[String]) -> i32 {
    10 * ab[0].parse::<i32>().unwrap() + ab[1].parse::<i32>().unwrap()
}

fn main() {
    let lines: Vec<String> = std::io::stdin()
        .lock()
        .lines()
        .map(|s| s.unwrap())
        .collect();

    let initial: i32 = join_into_int(&lines[..2]);
    let change_abses: Vec<i32> = lines[2..lines.len() - 1]
        .chunks(2)
        .map(join_into_int)
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
