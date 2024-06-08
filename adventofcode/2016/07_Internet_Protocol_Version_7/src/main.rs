use regex::Regex;
use std::io::{self, BufRead};

fn bracketed_parts(src: &str) -> Vec<String> {
    Regex::new(r"\[[a-z]+\]")
        .unwrap()
        .find_iter(src)
        .map(|x| {
            x.as_str()
                .strip_prefix('[')
                .unwrap()
                .strip_suffix(']')
                .unwrap()
                .to_string()
        })
        .collect()
}

fn top_level_parts(src: &str) -> Vec<String> {
    Regex::new(r"\[[a-z]+\]")
        .unwrap()
        .split(src)
        .map(|x| x.to_string())
        .collect()
}

fn has_an_abba(xs: &str) -> bool {
    xs.chars().collect::<Vec<_>>().windows(4).any(|abcd| {
        let [a, b, c, d] = abcd else {
            panic!("{:?} isn't a quad", abcd)
        };
        a != b && b == c && a == d
    })
}

fn have_an_abba(xss: &[String]) -> bool {
    xss.iter().any(|xs| has_an_abba(xs))
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().to_string())
        .collect();

    let result = lines
        .into_iter()
        .filter(|line| {
            let xs = top_level_parts(line);
            let ys = bracketed_parts(line);
            have_an_abba(&xs) && !have_an_abba(&ys)
        })
        .count();

    println!("{}", result);
}
