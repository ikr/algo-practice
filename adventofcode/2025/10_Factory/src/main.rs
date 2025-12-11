use pathfinding::prelude::astar;
use std::io::{BufRead, stdin};

fn heu_dist(mut a: Vec<i16>, mut b: Vec<i16>) -> u16 {
    assert!(
        a.iter().zip(b.iter()).all(|(x, y)| x <= y) || a.iter().zip(b.iter()).all(|(x, y)| x >= y)
    );

    if a.iter().zip(b.iter()).all(|(x, y)| x >= y) {
        (a, b) = (b, a);
    }

    let mut result: u16 = 0;

    while let Some(delta) = a
        .iter()
        .zip(b.iter())
        .filter(|(x, y)| **x != **y)
        .min_by_key(|(x, y)| **y - **x)
        .map(|(x, y)| y - x)
    {
        assert!(delta > 0);
        for i in 0..a.len() {
            if a[i] != b[i] {
                a[i] += delta;
            }
        }
        result += delta as u16;
    }

    result
}

#[derive(Clone, Debug)]
struct Machine {
    end_joltage: Vec<i16>,
    buttons: Vec<Vec<usize>>,
}

impl Machine {
    fn decode_end_joltage(s: &str) -> Vec<i16> {
        s.strip_prefix('{')
            .and_then(|s| s.strip_suffix('}'))
            .unwrap()
            .split(',')
            .map(|sub| sub.parse().unwrap())
            .collect()
    }

    fn decode_button(s: &str) -> Vec<usize> {
        s.strip_prefix('(')
            .and_then(|s| s.strip_suffix(')'))
            .unwrap()
            .split(',')
            .map(|sub| sub.parse().unwrap())
            .collect()
    }

    fn decode(s: &str) -> Self {
        let parts: Vec<_> = s.split(' ').collect();
        let n = parts.len();

        let end_joltage = Self::decode_end_joltage(parts[n - 1]);

        let buttons = parts[1..n - 1]
            .iter()
            .map(|&s| Self::decode_button(s))
            .collect();

        Self {
            end_joltage,
            buttons,
        }
    }

    fn initial_joltage(&self) -> Vec<i16> {
        vec![0; self.end_joltage.len()]
    }

    fn adjacent(&self, u: &[i16]) -> Vec<(Vec<i16>, u16)> {
        self.buttons
            .iter()
            .filter_map(|bi| {
                let mut result: Vec<i16> = u.to_vec();
                for &i in bi {
                    result[i] += 1;

                    if result[i] > self.end_joltage[i] {
                        return None;
                    }
                }
                Some((result, 1))
            })
            .collect()
    }

    fn min_presses(&mut self) -> u16 {
        astar(
            &self.initial_joltage(),
            |u| self.adjacent(u),
            |u| heu_dist(u.to_vec(), self.end_joltage.clone()),
            |u| *u == self.end_joltage,
        )
        .expect("Assumed path exists")
        .1
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let machines: Vec<Machine> = lines.into_iter().map(|s| Machine::decode(&s)).collect();
    let min_presses: Vec<usize> = machines
        .into_iter()
        .map(|mut m| {
            let result = m.min_presses() as usize;
            eprintln!("{:?} in {result} presses", m.end_joltage);
            result
        })
        .collect();

    let result: usize = min_presses.into_iter().sum();
    println!("{result}");
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_heu_dist() {
        for (a, b, expected) in [
            (vec![1], vec![1], 0),
            (vec![3, 5, 4, 7], vec![1, 2, 2, 0], 7),
        ] {
            assert_eq!(heu_dist(a, b), expected);
        }
    }
}
