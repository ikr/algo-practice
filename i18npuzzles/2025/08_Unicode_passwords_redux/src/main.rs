use itertools::Itertools;
use std::{
    hash::Hash,
    io::{self, BufRead},
};
use unicode_normalization::UnicodeNormalization;

fn base_char(c: char) -> char {
    c.nfd().next().unwrap()
}

fn has_repeats<T: Eq + Hash>(xs: &[T]) -> bool {
    xs.iter().counts().into_values().any(|f| f != 1)
}

fn is_vowel(c: char) -> bool {
    ['A', 'E', 'I', 'O', 'U'].contains(&c)
}

fn canonize(s: String) -> String {
    s.to_uppercase().chars().map(base_char).collect()
}

fn is_valid(xs: &str) -> bool {
    let cs: Vec<char> = xs.chars().collect();
    let aa: Vec<char> = cs.iter().filter(|c| c.is_alphabetic()).copied().collect();

    cs.len() >= 4
        && cs.len() <= 12
        && cs.iter().any(|c| c.is_ascii_digit())
        && cs.iter().any(|c| is_vowel(*c))
        && cs.iter().any(|c| c.is_alphabetic() && !is_vowel(*c))
        && !has_repeats(&aa)
}

fn main() {
    let pws: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| canonize(line.unwrap()))
        .collect();

    let result = pws.into_iter().filter(|s| is_valid(s)).count();
    println!("{}", result);
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test_decomposition_a() {
        let xs: Vec<char> = 'Å'.nfd().collect();
        assert_eq!(xs, vec!['A', '\u{30a}']);
    }

    #[test]
    fn test_decomposition_b() {
        let xs: Vec<char> = 'ё'.nfd().collect();
        assert_eq!(xs, vec!['е', '\u{308}']);
    }

    #[test]
    fn base_char_works_a() {
        assert_eq!(base_char('Å'), 'A');
    }

    #[test]
    fn base_char_works_b() {
        assert_eq!(base_char('z'), 'z');
    }

    #[test]
    fn base_char_works_c() {
        assert_eq!(base_char('!'), '!');
    }
}
