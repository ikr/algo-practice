use std::io::{self, BufRead};

const NEEDLES: [&str; 5] = ["Οδυσσευσ", "Οδυσσεωσ", "Οδυσσει", "Οδυσσεα", "Οδυσσευ"];
const AL_HI: &str = "ΑΒΓΔΕΖΗΘΙΚΛΜΝΞΟΠΡΣΤΥΦΧΨΩ";
const AL_LO: &str = "αβγδεζηθικλμνξοπρστυφχψω";

fn remove_punctuation(s: String) -> String {
    s.chars()
        .filter(|c| c.is_lowercase() || c.is_uppercase() || *c == ' ')
        .collect()
}

fn normalize_sigma(s: String) -> String {
    s.chars().map(|c| if c == 'ς' { 'σ' } else { c }).collect()
}

fn transcode(s: &str, shift: usize) -> String {
    s.chars()
        .map(|c| {
            if c.is_alphabetic() {
                if let Some(i) = AL_HI.chars().position(|x| x == c) {
                    let aa: Vec<char> = AL_HI.chars().collect();
                    aa[(i + shift) % aa.len()]
                } else if let Some(i) = AL_LO.chars().position(|x| x == c) {
                    let aa: Vec<char> = AL_LO.chars().collect();
                    aa[(i + shift) % aa.len()]
                } else {
                    panic!("Unexpected letter {}", c)
                }
            } else {
                assert_eq!(c, ' ');
                c
            }
        })
        .collect()
}

fn contains_odysseus(haystack: &str) -> bool {
    NEEDLES.iter().any(|&needle| haystack.contains(needle))
}

fn any_transcoding_contains_odysseus(haystack: &str) -> bool {
    (0..AL_HI.len()).any(|shift| contains_odysseus(&transcode(haystack, shift)))
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.expect("Next stdin line available"))
        .map(remove_punctuation)
        .map(normalize_sigma)
        .collect();

    let result = lines
        .into_iter()
        .filter(|s| any_transcoding_contains_odysseus(s))
        .count();
    eprintln!("{}", result);
}
