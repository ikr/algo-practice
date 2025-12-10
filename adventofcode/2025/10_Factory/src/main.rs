use std::{
    collections::HashMap,
    io::{BufRead, stdin},
};

const INF: u16 = 50_000;

fn sub<T: std::ops::Sub<Output = T> + Copy>(a: Vec<T>, b: Vec<T>) -> Vec<T> {
    a.into_iter().zip(b).map(|(x, y)| x - y).collect()
}

#[derive(Clone, Debug)]
struct Machine {
    end_joltage: Vec<i16>,
    buttons: Vec<Vec<usize>>,
    memo: HashMap<(u8, Vec<i16>), u16>,
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

        let memo = HashMap::new();

        Self {
            end_joltage,
            buttons,
            memo,
        }
    }

    fn button_bump(&self, button_index: usize) -> Vec<i16> {
        let mut result = vec![0; self.end_joltage.len()];
        for &i in &self.buttons[button_index] {
            result[i] = 1;
        }
        result
    }

    fn recur(&mut self, num_buttons_used: u8, joltage: Vec<i16>) -> u16 {
        if joltage.iter().any(|&x| x < 0) {
            return INF;
        }

        if num_buttons_used == 0 {
            return INF;
        }

        if joltage.iter().all(|&x| x == 0) {
            return 0;
        }

        let key = (num_buttons_used, joltage.clone());

        if let Some(&cached) = self.memo.get(&key) {
            cached
        } else {
            let value: u16 = self.recur(num_buttons_used - 1, joltage.clone()).min({
                let bump = self.button_bump((num_buttons_used - 1) as usize);
                let sub = sub(joltage, bump);
                1 + self.recur(num_buttons_used, sub)
            });

            self.memo.insert(key, value);
            value
        }
    }

    fn min_presses(&mut self) -> u16 {
        self.recur(self.buttons.len() as u8, self.end_joltage.clone())
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let machines: Vec<Machine> = lines.into_iter().map(|s| Machine::decode(&s)).collect();
    let min_presses: Vec<usize> = machines
        .into_iter()
        .map(|mut m| {
            eprint!(".");
            m.min_presses() as usize
        })
        .collect();
    eprintln!();

    let result: usize = min_presses.into_iter().sum();
    println!("{result}");
}
