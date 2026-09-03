use std::{
    fmt::Debug,
    io::{self, BufRead},
    str::FromStr,
};

const LIM: usize = 10_000;

fn decode<T>(src: &str) -> T
where
    T: FromStr,
    T::Err: Debug,
{
    src.parse::<T>().unwrap()
}

fn decode_csv<T>(src: &str) -> Vec<T>
where
    T: FromStr,
    T::Err: Debug,
{
    src.split(',').map(|a| decode(a)).collect()
}

struct State {
    visited: [[bool; LIM]; 2],
    jump_lengths_stack: Vec<usize>,
    phase: usize,
    current: usize,
}

impl State {
    fn new(mut jump_lengths: Vec<usize>) -> Self {
        jump_lengths.reverse();
        Self {
            visited: {
                let mut row0 = [false; LIM];
                row0[0] = true;
                [row0, [false; LIM]]
            },
            jump_lengths_stack: jump_lengths,
            phase: 0,
            current: 0,
        }
    }

    fn next(&mut self) {
        if let Some(delta) = self.jump_lengths_stack.pop() {
            self.phase = (self.phase + 1) % 2;
            let previous = self.current;

            if self.current > delta && !self.visited[self.phase][self.current - delta] {
                self.current -= delta;
            } else {
                self.current += delta;

                while self.visited[self.phase][self.current] {
                    self.current += 1;
                }
            }

            assert_ne!(previous, self.current);
            let (lo, hi) = (previous.min(self.current), previous.max(self.current));

            for i in lo..=hi {
                self.visited[self.phase][i] = true;
            }
        }
    }
}

fn simulate_return_final_point(jump_lengths: Vec<usize>) -> usize {
    let mut s = State::new(jump_lengths);
    while !s.jump_lengths_stack.is_empty() {
        s.next();
    }
    s.current
}

fn main() {
    let lines: Vec<String> = io::stdin().lock().lines().map(|x| x.unwrap()).collect();
    let xss: Vec<Vec<usize>> = lines.into_iter().map(|line| decode_csv(&line)).collect();
    let rs: Vec<usize> = xss.into_iter().map(simulate_return_final_point).collect();
    eprintln!("{rs:?}");
    println!("{}", rs.into_iter().sum::<usize>());
}
