use std::{
    fmt::Debug,
    io::{self, BufRead},
    str::FromStr,
};

const INF: usize = 2_000;

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

#[derive(Clone, Copy)]
struct Itvl {
    a: usize,
    b: usize,
}

impl Itvl {
    fn new(a: usize, b: usize) -> Self {
        assert!(a < b);
        Self { a, b }
    }

    fn is_edge(self, x: usize) -> bool {
        self.a == x || self.b == x
    }

    fn is_disjoing_with(self, other: Self) -> bool {
        (self.b < other.a) || (other.b < self.a)
    }

    fn is_congruent_with(self, other: Self) -> bool {
        (other.a < self.a && self.b < other.b) || (self.a < other.a && other.b < self.b)
    }
}

struct State {
    arcs: Vec<Vec<Itvl>>,
    jump_lengths_stack: Vec<usize>,
    phase: usize,
    point: usize,
}

impl State {
    fn new(mut jump_lengths: Vec<usize>) -> Self {
        jump_lengths.reverse();

        Self {
            arcs: vec![vec![]; 2],
            jump_lengths_stack: jump_lengths,
            phase: 1,
            point: 0,
        }
    }

    fn is_visited(&self, x: usize) -> bool {
        self.arcs
            .iter()
            .any(|ivs| ivs.iter().any(|iv| iv.is_edge(x)))
    }

    fn is_possible(&self, iv: Itvl) -> bool {
        self.arcs[self.phase]
            .iter()
            .all(|ab| ab.is_disjoing_with(iv) || ab.is_congruent_with(iv))
    }

    fn flip_phase(&mut self) {
        self.phase = (self.phase + 1) % 2;
    }

    fn next(&mut self) {
        if let Some(delta) = self.jump_lengths_stack.pop() {
            let previous = self.point;
            self.flip_phase();

            if self.point > delta
                && !self.is_visited(self.point - delta)
                && self.is_possible(Itvl::new(self.point - delta, self.point))
            {
                self.point -= delta;
            } else {
                self.point += delta;

                while self.point < INF
                    && (self.is_visited(self.point)
                        || !self.is_possible(Itvl::new(previous, self.point)))
                {
                    self.point += 1;
                }

                if self.point == INF {
                    self.point = previous;
                    self.flip_phase();
                    return;
                }
            }

            assert_ne!(previous, self.point);
            let (lo, hi) = (previous.min(self.point), previous.max(self.point));
            self.arcs[self.phase].push(Itvl::new(lo, hi));
        }
    }
}

fn simulate_return_final_point(jump_lengths: Vec<usize>) -> usize {
    let mut s = State::new(jump_lengths);
    while !s.jump_lengths_stack.is_empty() {
        s.next();
    }
    s.point
}

fn main() {
    let lines: Vec<String> = io::stdin().lock().lines().map(|x| x.unwrap()).collect();
    let xss: Vec<Vec<usize>> = lines.into_iter().map(|line| decode_csv(&line)).collect();
    let rs: Vec<usize> = xss.into_iter().map(simulate_return_final_point).collect();
    println!("{}", rs.into_iter().sum::<usize>());
}
