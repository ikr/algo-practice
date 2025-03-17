use bcrypt::verify;
use itertools::Itertools;
use std::{
    collections::HashMap,
    io::{self, BufRead},
};
use unicode_normalization::{UnicodeNormalization, is_nfc};

fn parse_pair(s: &String) -> (String, String) {
    let parts: Vec<_> = s.split_whitespace().collect();
    (parts[0].to_string(), parts[1].to_string())
}

fn is_decomposable(c: char) -> bool {
    c.nfd().count() != 1
}

fn decomposable_indices(cs: &[char]) -> Vec<usize> {
    cs.iter()
        .enumerate()
        .filter(|(_, c)| is_decomposable(**c))
        .map(|(i, _)| i)
        .collect()
}

fn any_variation_hash_matches(password: &str, target_hash: &str) -> bool {
    assert!(is_nfc(&password));
    let cs: Vec<char> = password.chars().collect();
    let all_ii = decomposable_indices(&cs);

    for ii in all_ii.into_iter().powerset() {
        let mut cur: Vec<char> = vec![];

        for (j, c) in cs.iter().enumerate() {
            if ii.contains(&j) {
                cur.extend(c.nfd());
            } else {
                cur.push(*c);
            }
        }

        if verify(&cur.into_iter().collect::<String>(), target_hash).expect("Valid bcrypt hash") {
            return true;
        }
    }

    false
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap())
        .collect();

    let isep = lines.iter().position(|s| s.is_empty()).unwrap();

    let hashes_by_username: HashMap<String, String> =
        lines[..isep].iter().map(parse_pair).collect();

    let login_attempts: Vec<(String, String)> = lines[isep + 1..]
        .iter()
        .map(parse_pair)
        .map(|(u, p)| (u, p.nfc().to_string()))
        .collect();

    let result = login_attempts
        .into_iter()
        .filter(|(username, password)| {
            if let Some(h) = hashes_by_username.get(username) {
                any_variation_hash_matches(&password, h)
            } else {
                false
            }
        })
        .count();

    println!("{}", result);
}

#[cfg(test)]
mod tests {

    use super::*;

    #[test]
    fn verify_bcrypt_example() {
        assert_eq!(
            verify(
                "secret",
                "$2b$10$v3I80pwHtgxp2ampg4Opy.hehc03wCR.JBZE6WHsrSQtxred57/PG"
            )
            .unwrap(),
            true
        );
    }

    #[test]
    fn is_decomposable_yes() {
        assert!(is_decomposable('È'));
    }

    #[test]
    fn is_decomposable_no() {
        assert!(!is_decomposable('E'));
    }
}
