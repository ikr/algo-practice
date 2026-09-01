#![warn(clippy::all)]
#![warn(clippy::pedantic)]
#![warn(clippy::nursery)]
#![warn(clippy::cargo)]

use std::{
    collections::HashSet,
    fmt::Debug,
    hash::Hash,
    io::{self, BufRead},
    iter::successors,
    str::FromStr,
};

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

fn split_last<T>(mut xs: Vec<T>) -> Option<(T, Vec<T>)> {
    xs.pop().map(|x| (x, xs))
}

fn with<T: Eq + Hash>(mut xs: HashSet<T>, x: T) -> HashSet<T> {
    xs.insert(x);
    xs
}

type Int = u16;

struct State {
    visited: HashSet<Int>,
    jump_lengths_stack: Vec<Int>,
    current: Int,
}

impl State {
    fn new(mut jump_lengths: Vec<Int>) -> Self {
        jump_lengths.reverse();
        Self {
            visited: HashSet::new(),
            jump_lengths_stack: jump_lengths,
            current: 0,
        }
    }

    fn next(self) -> Option<Self> {
        split_last(self.jump_lengths_stack).map(|(delta, jump_lengths_stack)| {
            let current = if self.current > delta && !self.visited.contains(&(self.current - delta))
            {
                self.current - delta
            } else {
                self.current + delta
            };

            let visited = with(self.visited, current);
            Self {
                visited,
                jump_lengths_stack,
                current,
            }
        })
    }
}

fn simulate_return_final_point(jump_lengths: Vec<Int>) -> Int {
    let mut s = State::new(jump_lengths);
    while let Some(t) = s.next() {
        s = t
    }
    s.current
}

fn main() {
    let lines: Vec<String> = io::stdin().lock().lines().map(|x| x.unwrap()).collect();
    let xss: Vec<Vec<u16>> = lines.into_iter().map(|line| decode_csv(&line)).collect();
    eprintln!("{xss:?}");
}
