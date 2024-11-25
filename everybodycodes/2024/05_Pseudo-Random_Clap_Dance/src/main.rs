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
    xs: VecDeque<u16>,
}

impl Chain {
    fn do_clapping(&mut self) {
        let x0 = self.xs.pop_front().unwrap();
        let n = self.xs.len() as u16;
        let r = (x0 - 1) % (2 * n);

        if r < n {
            self.xs.insert(r as usize, x0);
        } else {
            let rr = r - n;
            self.xs.insert((n - rr) as usize, x0);
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
        let xs = self
            .chains
            .iter()
            .map(|c| c.xs.front().unwrap().to_string())
            .collect::<Vec<_>>();

        xs.join("").parse().unwrap()
    }
}

fn main() {
    let rows: Vec<Vec<u16>> = io::stdin()
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

    let mut result: u64 = 0;
    let mut m = Machine::new(column_chains);
    let hi = 10u64.pow(11);
    //let hi = 10;
    for _ in 1u64..=hi {
        m.play_round();
        let candidate = m.current_result();
        //eprintln!("{}", candidate);

        if candidate > result {
            println!("{}", candidate);
            result = candidate;
        }
    }
}
