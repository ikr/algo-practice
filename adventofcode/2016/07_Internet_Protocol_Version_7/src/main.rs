use regex::Regex;
use std::{
    collections::HashSet,
    io::{self, BufRead},
};

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

fn is_aba(abc: &str) -> bool {
    let [a, b, c] = abc.chars().collect::<Vec<char>>()[..] else {
        panic!("{:?} isn't a triple", abc)
    };
    a != b && a == c
}

fn abas_of(xs: &str) -> HashSet<String> {
    xs.chars()
        .collect::<Vec<_>>()
        .windows(3)
        .map(|ys| ys.iter().collect::<String>())
        .filter(|ys| is_aba(ys))
        .collect()
}

fn all_abas(xss: &[String]) -> HashSet<String> {
    xss.iter().fold(HashSet::new(), |acc, xs| {
        acc.union(&abas_of(xs)).map(|x| x.to_string()).collect()
    })
}

fn bab(aba: &str) -> String {
    let [a, b, _] = aba.chars().collect::<Vec<char>>()[..] else {
        panic!("{:?} isn't a triple", aba)
    };
    [b, a, b].iter().collect()
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().to_string())
        .collect();

    let result1 = lines
        .iter()
        .filter(|line| {
            let xs = top_level_parts(line);
            let ys = bracketed_parts(line);
            have_an_abba(&xs) && !have_an_abba(&ys)
        })
        .count();

    println!("{}", result1);

    let result2 = lines
        .into_iter()
        .filter(|line| {
            let xs = top_level_parts(line);
            let babs: Vec<String> = all_abas(&xs).into_iter().map(|x| bab(&x)).collect();

            let ys = bracketed_parts(line);
            let abas = all_abas(&ys);
            babs.into_iter().any(|bab| abas.contains(&bab))
        })
        .count();
    println!("{}", result2);
}
