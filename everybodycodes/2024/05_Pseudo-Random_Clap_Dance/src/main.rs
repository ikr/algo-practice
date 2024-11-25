use std::{
    collections::{HashMap, VecDeque},
    io::{self, BufRead},
};

fn transpose<T>(grid: Vec<Vec<T>>) -> Vec<Vec<T>> {
    assert!(!grid.is_empty());
    let h = grid[0].len();
    let mut iters: Vec<_> = grid.into_iter().map(|n| n.into_iter()).collect();
    (0..h)
        .map(|_| {
            iters
                .iter_mut()
                .map(|n| n.next().unwrap())
                .collect::<Vec<T>>()
        })
        .collect()
}

#[derive(Debug)]
struct Chain {
    xs: VecDeque<u8>,
}

impl Chain {
    fn do_clapping(&mut self) {
        let n = self.xs.len() as u8;
        let x0 = self.xs.pop_front().unwrap();
        let r = x0 % (2 * n);

        if r <= n {
            self.xs.insert((r - 1) as usize, x0);
        } else {
            let rr = r - n;
            self.xs.insert((n - 1 - rr) as usize, x0);
        }
    }
}

#[derive(Debug)]
struct Machine {
    chains: Vec<Chain>,
    current_chain: usize,
}

impl Machine {
    fn new(chains: Vec<Chain>) -> Self {
        Self {
            chains,
            current_chain: 0,
        }
    }

    fn play_round(&mut self) {
        let x0 = self.chains[self.current_chain].xs.pop_front().unwrap();
        let next_chain = (self.current_chain + 1) % self.chains.len();
        self.chains[next_chain].xs.push_front(x0);

        self.chains[next_chain].do_clapping();
        self.current_chain = next_chain;
    }

    fn current_result(&self) -> u64 {
        let n = self.chains.len() as u64;
        let ms = (0..n)
            .rev()
            .map(|i| 10u64.pow(i as u32))
            .collect::<Vec<_>>();
        let xs = self
            .chains
            .iter()
            .map(|c| c.xs.front().unwrap())
            .copied()
            .collect::<Vec<_>>();
        ms.iter().zip(xs.iter()).map(|(m, x)| m * (*x as u64)).sum()
    }
}

fn main() {
    let rows: Vec<Vec<u8>> = io::stdin()
        .lock()
        .lines()
        .map(|line| {
            line.unwrap()
                .split_whitespace()
                .map(|s| s.parse().unwrap())
                .collect()
        })
        .collect();

    let column_chains: Vec<Chain> = transpose(rows)
        .into_iter()
        .map(|xs| Chain {
            xs: xs.into_iter().collect::<VecDeque<_>>(),
        })
        .collect();

    let mut freqs: HashMap<u64, u64> = HashMap::new();
    let mut m = Machine::new(column_chains);
    for round in 1u64..10u64.pow(9) {
        m.play_round();
        let result = m.current_result();

        freqs.entry(result).and_modify(|e| *e += 1).or_insert(1);
        let f = freqs[&result];
        if f == 2024 {
            println!(
                "round: {} result: {} puzzle-answer: {}",
                round,
                result,
                round * result
            );
            break;
        }
    }
}
