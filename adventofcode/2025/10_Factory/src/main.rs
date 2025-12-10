use std::{
    collections::{HashMap, VecDeque},
    io::{BufRead, stdin},
};

#[derive(Clone, Debug)]
struct Machine {
    end_counts: Vec<u16>,
    bump_indices: Vec<Vec<usize>>,
}

impl Machine {
    fn decode_end_counts(s: &str) -> Vec<u16> {
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

        let bump_indices = parts[1..n - 1]
            .iter()
            .map(|&s| Self::decode_button(s))
            .collect();

        Self {
            end_counts,
            bump_indices,
        }
    }

    fn initial_counts(&self) -> Vec<u16> {
        vec![0; self.end_counts.len()]
    }

    fn adjacent(&self, u: &[u16]) -> Vec<Vec<u16>> {
        self.bump_indices
            .iter()
            .map(|bi| {
                let mut result: Vec<u16> = u.to_vec();
                for i in bi {
                    result[*i] += 1;
                }
                result
            })
            .collect()
    }

    fn min_presses(&self) -> usize {
        let mut dist: HashMap<Vec<u16>, usize> = HashMap::from([(self.initial_counts(), 0)]);
        let mut q: VecDeque<Vec<u16>> = VecDeque::from([self.initial_counts()]);

        while let Some(u) = q.pop_front() {
            for v in self.adjacent(&u) {
                if !dist.contains_key(&v) {
                    if v == self.end_counts {
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
    let result: usize = min_presses.into_iter().sum();
    println!("{result}");
}
