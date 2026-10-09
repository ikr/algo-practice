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

    eprintln!("{exposures:?}");

    let mut result: Vec<char> = vec![' '; n];

    for (i, exps) in exposures.into_iter().enumerate() {
        for (a, b) in exps {
            let j = timed_colors.partition_point(|(t, _)| *t <= a);

            if let Some(&(tc, c)) = timed_colors.get(j)
                && tc < b
            {
                assert!(a < tc && tc < b);
                result[i] = c;
                eprintln!("{result:?}");
            }
        }
    }

    result.into_iter().collect()
}

fn brute_force_final_colors(n: usize, commands: Vec<Command>) -> String {
    let mut blocked: Vec<bool> = vec![false; n];
    let mut result: Vec<char> = vec!['.'; n];

    for command in commands {
        match command {
            Command::FlipTile(i) => blocked[i] = !blocked[i],
            Command::Color(c) => {
                for (i, x) in result.iter_mut().enumerate() {
                    if !blocked[i] {
                        *x = c;
                    }
                }
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

    //let expected_result = brute_force_final_colors(n, commands.clone());
    let result = final_colors(n, commands);
    //assert_eq!(result, expected_result);

    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}

#[cfg(test)]
mod tests {
    use super::*;
    use rand::Rng;

    fn random_input() -> (usize, usize, Vec<Command>) {
        let mut rng = rand::thread_rng();
        let n = rng.gen_range(1..=2);
        let q = rng.gen_range(1..=6);
        let mut commands = Vec::with_capacity(q);
        for _ in 0..q {
            if rng.gen_bool(0.5) {
                let i = rng.gen_range(0..n);
                commands.push(Command::FlipTile(i));
            } else {
                let c = rng.gen_range('a'..='z');
                commands.push(Command::Color(c));
            }
        }
        (n, q, commands)
    }

    fn print_input(n: usize, q: usize, commands: &[Command]) {
        eprintln!("{n} {q}");
        for cmd in commands {
            match cmd {
                Command::FlipTile(i) => eprintln!("1 {}", i + 1),
                Command::Color(c) => eprintln!("2 {c}"),
            }
        }
    }

    #[test]
    fn test_final_colors_against_brute_force() {
        for _ in 0..1000 {
            let (n, q, base_commands) = random_input();
            let mut all_commands = Vec::with_capacity(base_commands.len() + 2);
            all_commands.push(Command::Color('a'));
            all_commands.push(Command::Color('a'));
            all_commands.extend_from_slice(&base_commands);
            let result = final_colors(n, all_commands.clone());
            let expected = brute_force_final_colors(n, all_commands.clone());
            if result != expected {
                print_input(n, q, &base_commands);
                panic!("final_colors ({result}) != brute_force_final_colors ({expected})");
            }
        }
    }
}
