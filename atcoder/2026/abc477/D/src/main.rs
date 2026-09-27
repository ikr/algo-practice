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

    todo!()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! { n: usize, q: usize, }
    let mut commands: Vec<Command> = Vec::with_capacity(q);

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
