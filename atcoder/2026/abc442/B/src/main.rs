use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        xs: [u32; n],
    }

    let mut volume: u32 = 0;
    let mut playing: bool = false;

    for x in xs {
        match x {
            1 => {
                volume += 1;
            }
            2 => {
                volume = volume.saturating_sub(1);
            }
            3 => {
                playing = !playing;
            }
            _ => unreachable!(),
        }

        let result = if playing && volume >= 3 { "Yes" } else { "No" };
        writeln!(writer, "{result}").unwrap();
    }

    writer.flush().unwrap();
}
