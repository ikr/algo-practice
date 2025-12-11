use std::io::{BufRead, stdin};
use z3::{Optimize, ast::Int};

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

    fn button_bump(&self, button_index: usize) -> Vec<i16> {
        let mut result = vec![0; self.end_joltage.len()];
        for &i in &self.buttons[button_index] {
            result[i] = 1;
        }
        result
    }

    fn min_presses(&mut self) -> u16 {
        let opt = Optimize::new();
        let k = self.buttons.len();
        let vs: Vec<Vec<i16>> = (0..k).map(|i| self.button_bump(i)).collect();
        let m = self.end_joltage.len();

        let coeffs: Vec<Int> = (0..k).map(|i| Int::new_const(format!("c_{i}"))).collect();

        for c in &coeffs {
            opt.assert(&c.ge(Int::from_i64(0)));
        }

        for j in 0..m {
            let mut terms = Vec::with_capacity(k);

            for i in 0..k {
                let vij = Int::from_i64(vs[i][j] as i64);
                terms.push(&coeffs[i] * vij);
            }

            let sum = Int::add(&terms.iter().collect::<Vec<_>>());
            opt.assert(&sum.eq(&Int::from_i64(self.end_joltage[j] as i64)));
        }

        let sum_coeffs = Int::add(&coeffs.iter().collect::<Vec<_>>());
        opt.minimize(&sum_coeffs);
        let result = opt.check(&[]);
        assert!(result == z3::SatResult::Sat);

        let model = opt.get_model().unwrap();
        let vals: Vec<u16> = coeffs
            .iter()
            .map(|c| model.eval(c, true).unwrap().as_i64().unwrap() as u16)
            .collect();
        vals.into_iter().sum()
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
