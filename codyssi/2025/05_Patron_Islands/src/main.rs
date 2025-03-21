use std::{
    collections::HashSet,
    io::{self, BufRead},
};

fn parse_line(s: &str) -> (i32, i32) {
    let parts: Vec<_> = s
        .strip_prefix('(')
        .and_then(|t| t.strip_suffix(')'))
        .unwrap()
        .split(", ")
        .collect();

    (parts[0].parse().unwrap(), parts[1].parse().unwrap())
}

fn main() {
    let mut xys: HashSet<(i32, i32)> = io::stdin()
        .lock()
        .lines()
        .map(|line| parse_line(&line.unwrap()))
        .collect();

    let mut cur = (0, 0);
    let mut result: i32 = 0;

    while let Some(nxt) = xys.clone().into_iter().min_by_key(|&(x, y)| {
        let (a, b) = cur;
        (x.abs_diff(a) + y.abs_diff(b), x, y)
    }) {
        xys.remove(&nxt);
        result += (cur.0.abs_diff(nxt.0) + cur.1.abs_diff(nxt.1)) as i32;
        cur = nxt;
    }
    println!("{}", result);
}
