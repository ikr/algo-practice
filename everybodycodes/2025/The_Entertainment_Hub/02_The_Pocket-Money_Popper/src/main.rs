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

fn represent(aa: &VecDeque<char>, bb: &VecDeque<char>) -> String {
    let xs: Vec<char> = aa.iter().chain(bb.iter()).cloned().collect();
    xs.into_iter()
        .map(|x| x.to_string())
        .collect::<Vec<_>>()
        .join(" ")
}

fn main() {
    input! {
        xs: Chars,
    }

    let mut ib: usize = 0;
    let mut result = 0;
    let (mut aa, mut bb) = initial_halves(&xs);
    assert_eq!(aa.len(), bb.len());
    //let mut aa: VecDeque<char> = "RGGBRGGB".chars().collect();
    //let mut bb: VecDeque<char> = "GGBRGGBR".chars().collect();
    eprintln!("{}", represent(&aa, &bb));

    while let Some(a) = aa.pop_front() {
        if a == BOLTS[ib] && (aa.len() + 1 + bb.len()) % 2 == 0 {
            bb.pop_front();
        }

        ib = (ib + 1) % BOLTS.len();
        if bb.len() > aa.len() {
            let b = bb.pop_front().unwrap();
            aa.push_back(b);
        }
        result += 1;

        eprintln!("{}", represent(&aa, &bb));
    }

    println!("{result}");
}
