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

    let (last_coloring_time, last_color) = *timed_colors.last().unwrap();
    let mut final_block_times: Vec<usize> = vec![0; n];
    let mut opening_times: Vec<Option<usize>> = vec![Some(1); n];

    for (j, command) in commands
        .into_iter()
        .enumerate()
        .filter(|&(i, _)| i < last_coloring_time)
    {
        match command {
            Command::FlipTile(t) => {
                if opening_times[t].is_some() {
                    final_block_times[t] = j;
                    opening_times[t] = None;
                } else {
                    opening_times[t] = Some(j);
                }
            }
            Command::Color(_) => {}
        }
    }

    let mut result: Vec<char> = vec![last_color; n];

    for (i, b) in final_block_times
        .into_iter()
        .enumerate()
        .filter(|(i, _)| opening_times[*i].is_none())
    {
        let j = timed_colors.partition_point(|(t, _)| *t < b);
        result[i] = timed_colors[j - 1].1;
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
