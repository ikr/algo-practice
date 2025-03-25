use regex::Regex;
use std::{
    collections::HashMap,
    io::{BufRead, stdin},
};

fn parse_initial_holding(s: &str) -> (String, i32) {
    let ps: Vec<_> = s.split(" HAS ").collect();
    (ps[0].to_string(), ps[1].parse().unwrap())
}

fn parse_movement(s: &str) -> (String, String, i32) {
    let re = Regex::new(r"^FROM ([A-Za-z-]+) TO ([A-Za-z-]+) AMT (\d+)$").unwrap();
    let caps = re.captures(s).unwrap();
    (
        caps[1].to_string(),
        caps[2].to_string(),
        caps[3].parse().unwrap(),
    )
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|s| s.unwrap()).collect();
    let isep: usize = lines.iter().position(|s| s.is_empty()).unwrap();

    let mut holdings: HashMap<String, i32> = lines[..isep]
        .iter()
        .map(|s| parse_initial_holding(s))
        .collect();

    let movements: Vec<_> = lines[isep + 1..]
        .iter()
        .map(|s| parse_movement(s))
        .collect();

    let mut debt: Vec<(String, String, i32)> = vec![];

    for (a, b, x0) in movements {
        let mut x = x0;

        while let Some(i) = debt.iter().position(|(debtor, _, _)| *debtor == b) {
            if x == 0 {
                break;
            }

            let (_, _, owed) = debt[i];
            let deduction = x.min(owed);
            x -= deduction;
            debt[i].2 -= deduction;

            debt = debt.into_iter().filter(|(_, _, x)| *x > 0).collect();
        }
    }

    let mut result: Vec<i32> = holdings.into_values().filter(|&x| x > 0).collect();
    result.sort_by_key(|x| -x);
    println!("{}", result[..3].iter().sum::<i32>());
}
