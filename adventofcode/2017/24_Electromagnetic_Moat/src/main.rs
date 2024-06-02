use std::io::{self, BufRead};

fn decode_pair(src: &str) -> [i32; 2] {
    let mut result: Vec<i32> = src.split('/').map(|part| part.parse().unwrap()).collect();
    result.sort();
    result.try_into().unwrap()
}

fn have_common_port(p: &[i32], q: &[i32]) -> bool {
    p.iter().any(|x| q.contains(x))
}

struct State {
    ps: Vec<[i32; 2]>,
}

impl State {
    fn max_strength_starting_with(&self, current: i32, used_bits: u64, p0: [i32; 2]) -> i32 {
        let mut result = current;
        for (i, p) in self.ps.iter().enumerate() {
            if (1u64 << i) & used_bits == 0u64 && have_common_port(&p0, p) {
                result = result.max(self.max_strength_starting_with(
                    current + p.iter().sum::<i32>(),
                    used_bits | (1u64 << i),
                    *p,
                ));
            }
        }
        result
    }
}

fn main() {
    let pairs: Vec<[i32; 2]> = io::stdin()
        .lock()
        .lines()
        .map(|line| decode_pair(&line.unwrap()))
        .collect();

    let (sources, segments): (Vec<_>, Vec<_>) = pairs.into_iter().partition(|ab| ab[0] == 0);

    let state = State { ps: segments };

    for s in sources {
        println!(
            "{:?}",
            state.max_strength_starting_with(s.iter().sum(), 0, s)
        );
    }
}
