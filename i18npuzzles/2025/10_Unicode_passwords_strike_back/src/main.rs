use bcrypt::verify;
use std::{
    collections::HashMap,
    io::{self, BufRead},
};
use unicode_normalization::UnicodeNormalization;

fn parse_pair(s: &String) -> (String, String) {
    let parts: Vec<_> = s.split_whitespace().collect();
    (parts[0].to_string(), parts[1].to_string())
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
    eprintln!("{:?}", hashes_by_username);

    let login_attempts: Vec<(String, String)> = lines[isep + 1..].iter().map(parse_pair).collect();
    eprintln!("{:?}", login_attempts);
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
}
