use proconio::input;
use proconio::marker::Bytes;
use proconio_derive::fastout;

enum Outcome {
    ConnieWins,
    ForrestWins,
    Uncertain,
    Draw,
}

#[derive(Clone, Copy, Debug)]
struct Four {
    first_column: usize,
    last_column: usize,
    lowest_row: usize,
}

fn detect_horizontal(grid: &[Vec<u8>], player: u8) -> Vec<Four> {
    let mut result: Vec<Four> = vec![];

    for ro in 0..6 {
        for co0 in 0..=3 {
            if grid[ro][co0..(co0 + 4)].iter().all(|x| *x == player) {
                result.push(Four {
                    first_column: co0,
                    last_column: co0 + 3,
                    lowest_row: ro,
                });
            }
        }
    }

    result
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
