use proconio::{input, marker::Usize1};
use std::io::{BufWriter, Write, stdout};

const T_INF: usize = 9_999_999;

#[derive(Clone, Copy, Debug)]
enum Command {
    FlipTile(usize),
    Color(char),
}

fn final_colors(n: usize, commands: Vec<Command>) -> String {
    let timed_colors: Vec<(usize, char)> = commands
        .iter()
        .enumerate()
        .filter_map(|(i, &command)| match command {
            Command::FlipTile(_) => None,
            Command::Color(c) => Some((i, c)),
        })
        .collect();

    // Exposures for every tile. Each exposure is a time interval [a, b]: tile opened at `a` and
    // then closed at `b`.
    let mut exposures: Vec<Vec<(usize, usize)>> = vec![vec![(0, T_INF)]; n];

    for (j, command) in commands.into_iter().enumerate() {
        match command {
            Command::FlipTile(t) => {
                let last_exporure: (usize, usize) = *exposures[t].last().unwrap();
                let (le_a, le_b) = last_exporure;

                if le_b == T_INF {
                    *exposures[t].last_mut().unwrap() = (le_a, j);
                } else {
                    exposures[t].push((j, T_INF))
                }
            }
            Command::Color(_) => {}
        }
    }

    let mut result: Vec<char> = vec![' '; n];

    for (i, exps) in exposures.into_iter().enumerate() {
        for (a, b) in exps {
            let j = timed_colors.partition_point(|(t, _)| *t < b);
            let (tc, c) = timed_colors[j - 1];

            if a < tc {
                result[i] = c;
            }
        }
    }

    result.into_iter().collect()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! { n: usize, q: usize, }
    let mut commands: Vec<Command> = Vec::with_capacity(q + 2);
    for _ in 0..2 {
        commands.push(Command::Color('a'));
    }

    for _ in 0..q {
        input! { opcode: u8 }

        match opcode {
            1 => {
                input! { i: Usize1 }
                commands.push(Command::FlipTile(i));
            }
            2 => {
                input! { c: char }
                commands.push(Command::Color(c));
            }
            _ => unreachable!(),
        }
    }

    let result = final_colors(n, commands);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
