use proconio::input;
use std::{
    collections::BinaryHeap,
    io::{BufWriter, Write, stdout},
};

#[derive(Clone, Copy, PartialOrd, Ord, PartialEq, Eq, Debug)]
enum Op {
    Open,
    Close,
}

fn total_slack_off_time(xs: Vec<i64>, t: i64) -> i64 {
    let mut q: BinaryHeap<(i64, Op)> = xs.into_iter().map(|x| (-x, Op::Close)).collect();
    q.push((-t, Op::Close));

    let mut result = 0;
    let mut mb_opening_time: Option<i64> = Some(0);

    while let Some((minus_x, op)) = q.pop() {
        let x = -minus_x;

        match (mb_opening_time, op) {
            (None, Op::Open) => {
                mb_opening_time = Some(x);
            }

            (Some(opening_time), Op::Close) => {
                assert!(opening_time <= x);
                result += x - opening_time;
                mb_opening_time = None;
                q.push((-x - 100, Op::Open));
            }

            _ => {}
        }
    }

    result
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        t: i64,
        xs: [i64; n],
    }

    let result = total_slack_off_time(xs, t);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
