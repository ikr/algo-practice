use std::io::{self, BufRead};

use regex::Regex;
use unicode_normalization::UnicodeNormalization;

#[derive(Clone, Debug)]
struct Name {
    first: String,
    last: String,
}

impl Name {
    fn english_sort_key(&self) -> (String, String) {
        let ab: Vec<String> = [&self.last, &self.first]
            .into_iter()
            .map(|src| {
                src.to_lowercase()
                    .replace("ı", "i")
                    .replace("æ", "ae")
                    .replace("'", "")
                    .replace("-", "")
                    .chars()
                    .map(|c| c.nfd().next().unwrap())
                    .collect()
            })
            .collect();
        (ab[0].clone(), ab[1].clone())
    }

    fn swedish_alphabet() -> Vec<char> {
        let mut result: Vec<char> = ('a'..='z').collect();
        result.extend(['å', 'ä', 'ö', ' ']);
        result
    }

    fn swedish_sort_key(&self) -> (Vec<usize>, Vec<usize>) {
        let az = Name::swedish_alphabet();
        let index_of = |c: char| -> usize {
            match az.iter().position(|&x| x == c) {
                Some(i) => i,
                None => panic!("{} not in the alphabet", c),
            }
        };
        let indicies = |s: &str| -> Vec<usize> { s.chars().map(index_of).collect() };

        let ab: Vec<_> = [&self.last, &self.first]
            .into_iter()
            .map(|src| {
                let s: String = src
                    .to_lowercase()
                    .replace("æ", "ä")
                    .replace("ı", "i")
                    .replace("ı", "i")
                    .replace("ø", "ö")
                    .replace("'", "")
                    .replace("-", "")
                    .chars()
                    .map(|c| {
                        if az.contains(&c) {
                            c
                        } else {
                            c.nfd().next().unwrap()
                        }
                    })
                    .collect();

                indicies(&s)
            })
            .collect();
        (ab[0].clone(), ab[1].clone())
    }

    fn canonize_last_name(&self) -> Name {
        let s = self.last.clone();
        let i0 = s.chars().position(|c| c.is_uppercase()).unwrap();

        Name {
            first: self.first.clone(),
            last: s.chars().skip(i0).collect(),
        }
    }

    fn dutch_sort_key(&self) -> (String, String) {
        self.canonize_last_name().english_sort_key()
    }
}

fn parse_line(s: &str) -> (Name, u64) {
    let re = Regex::new(r"^(.+), (.+): (\d+)$").unwrap();
    let caps = re.captures(s).unwrap();
    (
        Name {
            first: caps[2].to_string(),
            last: caps[1].to_string(),
        },
        caps[3].parse().unwrap(),
    )
}

fn median_number(lines: &[(Name, u64)]) -> u64 {
    let n = lines.len();
    lines[n / 2].1
}

fn main() {
    let mut lines: Vec<_> = io::stdin()
        .lock()
        .lines()
        .map(|line| parse_line(&line.unwrap()))
        .collect();
    eprintln!("{:?}", lines);

    lines.sort_by_key(|(n, _)| n.english_sort_key());
    eprintln!("{:?}", lines);
    let a = median_number(&lines);
    eprintln!("{}", a);

    lines.sort_by_key(|(n, _)| n.swedish_sort_key());
    eprintln!("{:?}", lines);
    let b = median_number(&lines);
    eprintln!("{}", b);

    lines.sort_by_key(|(n, _)| n.dutch_sort_key());
    eprintln!("{:?}", lines);
    let c = median_number(&lines);
    eprintln!("{}", c);

    println!("{}", a * b * c);
}
