use std::{
    collections::VecDeque,
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

        if x0 <= n {
            self.xs.insert((x0 - 1) as usize, x0);
        } else {
            let r = x0 - n;
            self.xs.insert((n - 1 - r) as usize, x0);
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

    let mut m = Machine::new(column_chains);
    for _ in 0..10 {
        m.play_round();
        println!("{}", m.current_result());
    }
}
