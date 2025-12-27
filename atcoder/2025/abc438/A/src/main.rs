use proconio::{input, marker::Usize1};
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        d: usize,
        f: Usize1,
    }

    let contest_dow = f;
    let new_year_dow = d % 7;
    let result = if new_year_dow <= contest_dow {
        contest_dow - new_year_dow
    } else {
        7 - new_year_dow + contest_dow
    } + 1;
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
