use std::io::{self, BufRead};

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap())
        .collect();

    let words: Vec<String> = lines[0]
        .strip_prefix("WORDS:")
        .unwrap()
        .split(',')
        .map(|s| s.trim().to_string())
        .collect();

    let mut result: usize = 0;

    for line in lines[2..].iter() {
        for word in words.iter() {
            let mut xs: Vec<u8> = word.bytes().collect();
            xs.reverse();
            let reversed_word = String::from_utf8(xs).unwrap();

            let variants: Vec<String> = if *word == reversed_word {
                vec![word.to_string()]
            } else {
                vec![word.to_string(), reversed_word]
            };

            for w in variants {
                let f = line.match_indices(&w).count();
                result += f * word.len();
            }
        }
    }

    println!("{}", result);
}
