use std::io::Read;

fn run_length_encoding(s: &str) -> Vec<(char, usize)> {
    s.chars().fold(vec![], |mut acc, x| {
        if let Some(e) = acc.last_mut()
            && e.0 == x
        {
            e.1 += 1;
        } else {
            acc.push((x, 1))
        }
        acc
    })
}

fn asum(k: usize) -> i32 {
    (k * (k + 1) / 2) as i32
}

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).unwrap();

    let deltas: Vec<i32> = run_length_encoding(buf.trim_end())
        .into_iter()
        .map(|(c, k)| match c {
            '^' => asum(k),
            'v' => -asum(k),
            _ => unreachable!(),
        })
        .collect();

    let result = deltas
        .into_iter()
        .scan(0, |state, x| {
            *state += x;
            Some(*state)
        })
        .max()
        .unwrap();

    eprintln!("{result}");
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_run_length_encoding() {
        for (xs, exp) in [
            ("", vec![]),
            ("^^^^^", vec![('^', 5)]),
            (
                "^^^v^^^^vvvvvvv",
                vec![('^', 3), ('v', 1), ('^', 4), ('v', 7)],
            ),
        ] {
            assert_eq!(run_length_encoding(xs), exp, "on {:?}", xs);
        }
    }
}
