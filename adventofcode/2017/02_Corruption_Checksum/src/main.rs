use regex::Regex;

fn parse_line(src: &str) -> Vec<i32> {
    let sep = Regex::new(r"\s+").unwrap();
    let tokens: Vec<&str> = sep.split(src).collect();
    tokens.iter().map(|s| s.parse().unwrap()).collect()
}

fn read_input() -> Vec<Vec<i32>> {
    let input = std::io::read_to_string(std::io::stdin()).unwrap();
    input.lines().map(parse_line).collect()
}

fn main() {
    let xss = read_input();
    let part_1_result: i32 = xss
        .iter()
        .map(|xs| xs.iter().max().unwrap() - xs.iter().min().unwrap())
        .sum();
    println!("{}", part_1_result);
}
