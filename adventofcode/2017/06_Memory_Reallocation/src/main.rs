use std::collections::HashSet;

fn evolve(mut xs: Vec<i32>) -> Vec<i32> {
    let hi: i32 = xs.iter().max().unwrap().clone();
    let hi_i: usize = xs.iter().position(|x| *x == hi).unwrap().clone();
    xs[hi_i] = 0;

    for i in 1..=hi {
        let j = (hi_i + i as usize) % xs.len();
        xs[j] += 1;
    }
    xs
}

fn main() {
    let input_line = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .to_string();
    let mut xs: Vec<i32> = input_line
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    for _ in 1..=2 {
        let mut seen: HashSet<Vec<i32>> = HashSet::new();
        seen.insert(xs.clone());
        let mut result = 0;

        loop {
            result += 1;
            xs = evolve(xs.clone());
            if seen.contains(&xs) {
                break;
            }
            seen.insert(xs.clone());
        }

        println!("{}", result);
    }
}
