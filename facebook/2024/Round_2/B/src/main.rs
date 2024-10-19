use proconio::input;
use proconio::marker::Bytes;
use proconio_derive::fastout;

enum Outcome {
    ConnieWins,
    ForrestWins,
    Uncertain,
    Draw,
}

fn solve(grid: Vec<Vec<u8>>) -> Outcome {
    Outcome::Uncertain
}

#[fastout]
fn main() {
    input! {
        cases_num: u16,
    }

    for t in 1..=cases_num {
        input! {
            grid: [Bytes; 6],
        }

        let result = solve(grid);
        println!(
            "Case #{}: {}",
            t,
            match result {
                Outcome::ConnieWins => 'C',
                Outcome::ForrestWins => 'F',
                Outcome::Uncertain => '?',
                Outcome::Draw => '0',
            }
        );
    }
}
