use std::{
    collections::HashSet,
    io::{self, BufRead},
};

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

fn is_nice_1(xs: &[u8]) -> bool {
    contains_at_least_k_vowels(3, xs) && contains_a_double(xs) && is_free_of_disallowed_pairs(xs)
}

fn has_pair_at_least_twice_nonoverlapping(xs: &[u8]) -> bool {
    let pairs: HashSet<String> = xs.windows(2).fold(HashSet::new(), |mut acc, ab| {
        acc.insert(String::from_utf8(ab.to_vec()).unwrap());
        acc
    });

    let haystack: String = String::from_utf8(xs.to_vec()).unwrap();
    for needle in pairs {
        if let Some(i) = haystack.find(&needle) {
            if let Some(j) = haystack.rfind(&needle) {
                assert!(j >= i);
                if j - i > 1 {
                    return true;
                }
            }
        }
    }

    false
}

fn has_split_pair(xs: &[u8]) -> bool {
    xs.windows(3).any(|abc| {
        let [a, _, c] = *abc else { return false };
        a == c
    })
}

fn is_nice_2(xs: &[u8]) -> bool {
    has_pair_at_least_twice_nonoverlapping(xs) && has_split_pair(xs)
}

fn main() {
    let words: Vec<Vec<u8>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().into_bytes())
        .collect();

    println!("{}", words.iter().filter(|w| is_nice_1(w)).count());
    println!("{}", words.into_iter().filter(|w| is_nice_2(w)).count());
}
