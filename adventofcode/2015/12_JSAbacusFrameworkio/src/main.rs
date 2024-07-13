use regex::Regex;

fn main() {
    let src: String = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .to_owned();

    let re = Regex::new(r"-?\d+").unwrap();
    let xs: Vec<i32> = re
        .find_iter(&src)
        .map(|s| s.as_str().parse().unwrap())
        .collect();
    println!("{}", xs.iter().sum::<i32>());
}
