fn run_length_encoding(xs: &[u32]) -> Vec<(u32, u32)> {
    let mut result: Vec<(u32, u32)> = vec![(xs[0], 1)];

    for &x in &xs[1..] {
        if x == result.last().unwrap().0 {
            result.last_mut().unwrap().1 += 1;
        } else {
            result.push((x, 1));
        }
    }
    result
}

fn cycle_the_chain(mut xs: Vec<(u32, u32)>) -> Vec<(u32, u32)> {
    if xs.len() < 2 {
        xs
    } else {
        if xs[0].0 == xs.last().unwrap().0 {
            xs[0].1 += xs.last().unwrap().1;
            xs.pop();
        }
        xs
    }
}

fn part_1_sum(xs: &[(u32, u32)]) -> u32 {
    match xs.len() {
        0 => 0,
        1 => {
            if xs[0].1 > 1 {
                xs[0].0 * xs[0].1
            } else {
                0
            }
        }
        _ => xs
            .iter()
            .filter(|(_, k)| *k > 1)
            .fold(0u32, |acc, (x, k)| acc + (k - 1u32) * x),
    }
}

fn part_2_sum(xs: &[u32]) -> u32 {
    let n = xs.len();
    assert!(n % 2 == 0);
    let d = n / 2;

    let mut result = 0;
    for (i, x) in xs.iter().enumerate() {
        if xs[(i + d) % n] == *x {
            result += x;
        }
    }
    result
}

fn main() {
    let digits: Vec<u32> = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .chars()
        .map(|c| c.to_digit(10).unwrap())
        .collect();

    println!(
        "{}",
        part_1_sum(&cycle_the_chain(run_length_encoding(&digits)))
    );

    println!("{}", part_2_sum(&digits));
}
