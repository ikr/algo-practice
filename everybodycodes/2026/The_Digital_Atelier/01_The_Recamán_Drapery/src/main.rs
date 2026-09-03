use std::{
    collections::HashSet,
    fmt::Debug,
    io::{self, BufRead},
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

type Int = u32;

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

    fn next(&mut self) {
        if let Some(delta) = self.jump_lengths_stack.pop() {
            if self.current > delta && !self.visited.contains(&(self.current - delta)) {
                self.current -= delta;
            } else {
                self.current += delta;

                while self.visited.contains(&(self.current)) {
                    self.current += 1;
                }
            }

            self.visited.insert(self.current);
        }
    }
}

fn simulate_return_final_point(jump_lengths: Vec<Int>) -> Int {
    let mut s = State::new(jump_lengths);
    while !s.jump_lengths_stack.is_empty() {
        s.next();
    }
    s.current
}

fn main() {
    let lines: Vec<String> = io::stdin().lock().lines().map(|x| x.unwrap()).collect();
    let xss: Vec<Vec<Int>> = lines.into_iter().map(|line| decode_csv(&line)).collect();
    let rs: Vec<Int> = xss.into_iter().map(simulate_return_final_point).collect();
    println!("{}", rs.into_iter().sum::<Int>());
}
