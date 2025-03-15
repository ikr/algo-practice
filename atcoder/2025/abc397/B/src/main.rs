use proconio::input;
use std::io::{self, BufWriter, Write};

fn solve(s: String) -> usize {
    let mut cs: Vec<char> = s.chars().collect();
    let mut result = 0;

    if cs[0] == 'o' {
        cs.insert(0, 'i');
        result += 1;
    }

    if *cs.last().unwrap() == 'i' {
        cs.push('o');
        result += 1;
    }

    while let Some(i) = cs.windows(2).position(|ab| ab[0] == ab[1]) {
        let x = cs[i];
        let y = if x == 'i' { 'o' } else { 'i' };
        cs.insert(i + 1, y);
        result += 1;
    }

    result
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        s: String,
    }

    let result = solve(s);
    writeln!(writer, "{}", result).unwrap();
    writer.flush().unwrap();
}
