use std::collections::VecDeque;

use proconio::input;
use proconio::marker::Chars;

const REPS: usize = 5;
const BOLTS: [char; 3] = ['R', 'G', 'B'];

fn initial_halves(pattern: &[char]) -> (VecDeque<char>, VecDeque<char>) {
    let full = pattern.repeat(REPS);
    let n = full.len();
    (
        full[..n / 2].iter().cloned().collect(),
        full[n / 2..].iter().cloned().collect(),
    )
}

fn main() {
    input! {
        xs: Chars,
    }

    let mut ib: usize = 0;
    let mut result = 0;
    let (mut aa, mut bb) = initial_halves(&xs);

    while let Some(a) = aa.pop_front() {
        if a == BOLTS[ib] {
            if (aa.len() + 1 + bb.len()) % 2 == 0 {
                bb.pop_front();
            } else {
                let b = bb.pop_front().unwrap();
                aa.push_back(b);
            }
        } else {
            ib = (ib + 1) % BOLTS.len();
            if !aa.is_empty() {
                result += 1;
            }

            let b = bb.pop_front().unwrap();
            aa.push_back(b);
        }
    }

    println!("{result}");
}
