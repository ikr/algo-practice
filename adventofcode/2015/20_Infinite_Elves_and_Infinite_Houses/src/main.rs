use itertools::Itertools;

const P: i64 = 36000000;

fn divisors(x: i64) -> Vec<i64> {
    let mut result = (1..=x)
        .take_while(|i| i * i <= x)
        .fold(vec![], |mut acc, i| {
            if x % i == 0 {
                acc.push(i);
                acc.push(x / i);
                acc
            } else {
                acc
            }
        });
    result.sort();
    result.into_iter().dedup().collect()
}

fn number_of_presents(house_number: i64) -> i64 {
    divisors(house_number).into_iter().map(|i| i * 10).sum()
}

fn main() {
    let result = (1..=P)
        .take_while(|i| number_of_presents(*i) < P)
        .max()
        .unwrap()
        + 1;
    println!("{}", result);
}
