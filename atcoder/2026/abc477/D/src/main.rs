use proconio::{input, marker::Usize1};
use std::io::{BufWriter, Write, stdout};

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

    let (last_coloring_time, _) = *timed_colors.last().unwrap();
    let mut block_spans: Vec<(usize, usize)> = vec![(0, 1); n];
    let mut opening_times: Vec<Option<usize>> = vec![Some(1); n];

    for (j, command) in commands
        .into_iter()
        .enumerate()
        .filter(|&(i, _)| i < last_coloring_time)
    {
        match command {
            Command::FlipTile(t) => {
                if let Some(i) = opening_times[t] {
                    block_spans[t] = (i, j);
                    opening_times[t] = None;
                } else {
                    opening_times[t] = Some(j);
                }
            }
            Command::Color(_) => {}
        }
    }

    todo!()
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
    assert_eq!(result.len(), n);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
