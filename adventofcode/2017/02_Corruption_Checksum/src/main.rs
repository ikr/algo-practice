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
    eprintln!("{:?}", read_input());
}
