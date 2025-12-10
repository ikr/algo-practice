use std::{
    collections::{HashMap, VecDeque},
    io::{BufRead, stdin},
};

fn sub<T: std::ops::Sub<Output = T> + Copy>(a: Vec<T>, b: Vec<T>) -> Vec<T> {
    a.into_iter().zip(b).map(|(x, y)| x - y).collect()
}

#[derive(Clone, Debug)]
struct Machine {
    end_counts: Vec<i16>,
    buttons: Vec<Vec<usize>>,
}

impl Machine {
    fn decode_end_counts(s: &str) -> Vec<i16> {
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

        let end_counts = Self::decode_end_counts(parts[n - 1]);

        let buttons = parts[1..n - 1]
            .iter()
            .map(|&s| Self::decode_button(s))
            .collect();

        Self {
            end_counts,
            buttons,
        }
    }

    fn initial_counts(&self) -> Vec<i16> {
        vec![0; self.end_counts.len()]
    }

    fn button_bump(&self, button_index: usize) -> Vec<i16> {
        let mut result = vec![0; self.end_counts.len()];
        for &i in &self.buttons[button_index] {
            result[i] = 1;
        }
        result
    }

    fn adjacent(&self, u: &[i16]) -> Vec<Vec<i16>> {
        self.buttons
            .iter()
            .filter_map(|bi| {
                let mut result: Vec<i16> = u.to_vec();
                for &i in bi {
                    result[i] += 1;

                    if result[i] > self.end_counts[i] {
                        return None;
                    }
                }
                Some(result)
            })
            .collect()
    }

    fn min_presses(&self) -> usize {
        let mut dist: HashMap<Vec<i16>, usize> = HashMap::from([(self.initial_counts(), 0)]);
        let mut q: VecDeque<Vec<i16>> = VecDeque::from([self.initial_counts()]);

        while let Some(u) = q.pop_front() {
            for v in self.adjacent(&u) {
                if !dist.contains_key(&v) {
                    if v == self.end_counts {
                        eprint!(".");
                        return *dist.get(&u).unwrap() + 1;
                    }

                    dist.insert(v.clone(), *dist.get(&u).unwrap() + 1);
                    q.push_back(v);
                }
            }
        }

        unreachable!()
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let machines: Vec<Machine> = lines.into_iter().map(|s| Machine::decode(&s)).collect();
    let min_presses: Vec<usize> = machines.into_iter().map(|m| m.min_presses()).collect();
    eprintln!();
    let result: usize = min_presses.into_iter().sum();
    println!("{result}");
}
