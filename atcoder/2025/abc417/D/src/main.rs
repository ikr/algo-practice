use proconio::{derive_readable, input};
use std::io::{BufWriter, Write, stdout};

#[derive_readable]
#[derive(Clone, Copy)]
struct Present {
    p: usize,
    a: usize,
    b: usize,
}

// T[i][j] is the mood after opening all the presents up to- and including the present i, given that
// the mood right before opening that present i was j
fn sequential_moods_table(presents: &[Present]) -> Vec<Vec<usize>> {
    todo!()
}

fn final_moods(presents: Vec<Present>) -> Vec<usize> {
    todo!()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        presents: [Present; n],
    }

    let results = final_moods(presents);
    for r in results {
        writeln!(writer, "{r}").unwrap();
    }
    writer.flush().unwrap();
}
