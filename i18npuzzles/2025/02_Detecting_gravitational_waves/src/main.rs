use std::io::{self, BufRead};

use chrono::DateTime;
use itertools::Itertools;

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap())
        .collect();

    let timestamps: Vec<i64> = lines
        .into_iter()
        .map(|s| DateTime::parse_from_rfc3339(&s).unwrap().timestamp())
        .collect();

    let result_timestamp: i64 = timestamps
        .into_iter()
        .counts()
        .into_iter()
        .max_by_key(|(_, f)| *f)
        .unwrap()
        .0;

    let result = DateTime::from_timestamp(result_timestamp, 0).unwrap();
    println!("{}", result.to_rfc3339());
}
