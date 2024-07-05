use std::io::{self, BufRead};

fn is_vowel(x: u8) -> bool {
    "aeiou".as_bytes().contains(&x)
}

fn contains_at_least_k_vowels(k: usize, xs: &[u8]) -> bool {
    xs.iter().filter(|x| is_vowel(**x)).count() >= k
}

fn contains_a_double(xs: &[u8]) -> bool {
    xs.windows(2).any(|ys| ys[0] == ys[1])
}

fn is_free_of_disallowed_pairs(xs: &[u8]) -> bool {
    let haystack = String::from_utf8(xs.to_vec()).unwrap();
    for sub in ["ab", "cd", "pq", "xy"] {
        if haystack.contains(sub) {
            return false;
        }
    }
    true
}

fn main() {
    let words: Vec<Vec<u8>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().into_bytes())
        .collect();
}
