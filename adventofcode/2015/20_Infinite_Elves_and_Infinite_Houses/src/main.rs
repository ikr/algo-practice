use itertools::Itertools;

const P: u32 = 36000000;

fn divisors(x: u32) -> Vec<u32> {
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

fn number_of_presents(house_number: u32) -> u32 {
    divisors(house_number).into_iter().map(|i| i * 10).sum()
}

fn solve_part_1() -> u32 {
    (1..=P)
        .take_while(|i| number_of_presents(*i) < P)
        .max()
        .unwrap()
        + 1
}

fn solve_part_2() -> usize {
    let mut presents: Vec<u32> = vec![0; (P + 1) as usize];
    for e in 1..=P {
        for m in 1..=50 {
            let h = (e * m) as usize;
            presents[h] += e * 11;
            if presents[h] >= P {
                return h;
            }
        }
    }
    P as usize
}

fn main() {
    println!("{}", solve_part_1());
    println!("{}", solve_part_2());
}
