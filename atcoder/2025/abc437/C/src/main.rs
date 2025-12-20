use proconio::input;
use std::io::{BufWriter, Write, stdout};

#[derive(Clone, Copy, Debug)]
struct Deer {
    w: i64,
    p: i64,
}

impl Deer {
    fn new(wp: (i64, i64)) -> Self {
        let (w, p) = wp;
        Self { w, p }
    }
}

#[derive(Clone, Copy, Debug)]
struct State {
    capacity: i64,
    riders: usize,
}

impl State {
    fn new(capacity: i64, riders: usize) -> Self {
        Self { capacity, riders }
    }
}

fn max_riders(deers: Vec<Deer>) -> usize {
    let n = deers.len();
    let mut tab: Vec<Vec<State>> = vec![vec![State::new(0, 0); 2]; n];
    //tab[0][0] =

    tab[n - 1].iter().map(|a| a.riders).max().unwrap()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        t: usize,
    }

    for _ in 0..t {
        input! {
            n: usize,
            ps: [(i64, i64); n],
        }

        let result = max_riders(ps.into_iter().map(Deer::new).collect());
        writeln!(writer, "{result}").unwrap();
    }
    writer.flush().unwrap();
}
