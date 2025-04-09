use std::io::{BufRead, stdin};

fn parse_range_from_line(s: &str) -> (usize, usize) {
    let ps: Vec<_> = s.split(" : ").collect();
    let ab: Vec<usize> = ps[1].split(" -> ").map(|x| x.parse().unwrap()).collect();
    (ab[0], ab[1])
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let (a, b) = parse_range_from_line(&lines[0]);
    assert_eq!(a, 0);

    let ms: Vec<usize> = lines
        .last()
        .and_then(|s| s.strip_prefix("Possible Moves : "))
        .unwrap()
        .split(", ")
        .map(|x| x.parse().unwrap())
        .collect();

    let mut dp: Vec<u128> = vec![0; b + 1];
    dp[0] = 1;
    for i in 0..dp.len() {
        for &m in ms.iter() {
            if i + m < dp.len() {
                dp[i + m] += dp[i];
            }
        }
    }

    eprintln!("{}", dp.last().unwrap());
}
