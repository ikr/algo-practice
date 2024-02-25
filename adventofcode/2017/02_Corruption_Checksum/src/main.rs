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

fn whole_division_result(xs: &[i32]) -> i32 {
    for (i, x) in xs.iter().enumerate() {
        for j in i + 1..xs.len() {
            let y = xs[j];
            if x % y == 0 {
                return x / y;
            }
            if y % x == 0 {
                return y / x;
            }
        }
    }
    panic!("Not found");
}

fn main() {
    let xss = read_input();

    let part_1_result: i32 = xss
        .iter()
        .map(|xs| xs.iter().max().unwrap() - xs.iter().min().unwrap())
        .sum();
    println!("{}", part_1_result);

    let part_2_result: i32 = xss.iter().map(|xs| whole_division_result(xs)).sum();
    println!("{}", part_2_result);
}
