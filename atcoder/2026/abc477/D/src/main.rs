use proconio::{input, marker::Usize1};
use std::io::{BufWriter, Write, stdout};

#[derive(Clone, Copy, Debug)]
enum Command {
    FlipTile(usize),
    Color(char),
}

fn final_colors(commands: Vec<Command>) -> String {
    todo!()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! { n: usize, q: usize, }

    let mut commands: Vec<Command> = vec![];
    commands.reserve(q);

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

    eprintln!("{commands:?}");

    let result = final_colors(commands);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
