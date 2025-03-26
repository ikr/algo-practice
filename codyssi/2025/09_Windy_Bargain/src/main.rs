use itertools::Itertools;
use regex::Regex;
use std::{
    collections::{HashMap, VecDeque},
    io::{BufRead, stdin},
};

fn parse_initial_holding(s: &str) -> (String, u32) {
    let ps: Vec<_> = s.split(" HAS ").collect();
    (ps[0].to_string(), ps[1].parse().unwrap())
}

fn parse_movement(s: &str) -> (String, String, u32) {
    let re = Regex::new(r"^FROM ([A-Za-z-]+) TO ([A-Za-z-]+) AMT (\d+)$").unwrap();
    let caps = re.captures(s).unwrap();
    (
        caps[1].to_string(),
        caps[2].to_string(),
        caps[3].parse().unwrap(),
    )
}

struct Ledger {
    ids: HashMap<String, usize>,
    holdings: Vec<u32>,
    ious: Vec<VecDeque<(usize, u32)>>,
}

impl Ledger {
    fn from(holdings_by_name: HashMap<String, u32>) -> Self {
        let ids: HashMap<String, usize> = holdings_by_name
            .keys()
            .sorted()
            .cloned()
            .enumerate()
            .map(|(i, name)| (name, i))
            .collect();

        let holdings: Vec<u32> =
            holdings_by_name
                .into_iter()
                .fold(vec![0; ids.len()], |mut acc, (name, amount)| {
                    acc[*ids.get(&name).unwrap()] = amount;
                    acc
                });

        let ious: Vec<VecDeque<(usize, u32)>> = vec![VecDeque::new(); ids.len()];
        Self {
            ids,
            holdings,
            ious,
        }
    }

    fn transfer(&mut self, src_id: usize, dst_id: usize, amount: u32) {
        assert_ne!(amount, 0);
        let cash = self.holdings[src_id].min(amount);
        self.holdings[src_id] -= cash;

        let owed = amount - cash;
        if owed != 0 {
            self.ious[src_id].push_back((dst_id, owed));
        }

        if cash != 0 {
            self.receive(dst_id, cash);
        }
    }

    fn receive(&mut self, id: usize, mut cash: u32) {
        let mut inbox: Vec<(usize, u32)> = vec![];

        while let Some((creditor_id, credited)) = self.ious[id].pop_front() {
            let downpayment: u32 = credited.min(cash);
            cash -= downpayment;
            inbox.push((creditor_id, downpayment));

            if downpayment != credited {
                self.ious[id].push_front((creditor_id, credited - downpayment));
                break;
            }

            if cash == 0 {
                break;
            }
        }

        if cash != 0 {
            self.holdings[id] += cash;
        }

        for (i, x) in inbox {
            self.receive(i, x);
        }
    }

    fn id(&self, name: &str) -> usize {
        *self.ids.get(name).unwrap()
    }

    fn result(&self) -> u32 {
        self.holdings.iter().filter(|&&x| x != 0).k_largest(3).sum()
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|s| s.unwrap()).collect();
    let isep: usize = lines.iter().position(|s| s.is_empty()).unwrap();

    let holdings: HashMap<String, u32> = lines[..isep]
        .iter()
        .map(|s| parse_initial_holding(s))
        .collect();

    let movements: Vec<_> = lines[isep + 1..]
        .iter()
        .map(|s| parse_movement(s))
        .collect();

    let mut ledger = Ledger::from(holdings);
    for (src, dst, amount) in movements {
        ledger.transfer(ledger.id(&src), ledger.id(&dst), amount);
    }
    println!("{}", ledger.result())
}
