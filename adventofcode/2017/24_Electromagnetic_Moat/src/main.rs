use memoize::memoize;
use std::io::{self, BufRead};

fn decode_pair(src: &str) -> [u8; 2] {
    let mut result: Vec<u8> = src.split('/').map(|part| part.parse().unwrap()).collect();
    result.sort();
    result.try_into().unwrap()
}

fn have_common_port(p: &[u8], q: &[u8]) -> bool {
    p.iter().any(|x| q.contains(x))
}

static mut ANS: u16 = 0;

#[memoize(Ignore: ps, Capacity: 59999999)]
fn max_strength_starting_with(ps: &[[u8; 2]], used_bits: u64, p0: [u8; 2]) -> u16 {
    let mut result: u16 = p0.iter().sum::<u8>() as u16;
    for (i, p) in ps.iter().enumerate() {
        if (1u64 << i) & used_bits == 0u64 && have_common_port(&p0, p) {
            result = result.max(
                p0.iter().sum::<u8>() as u16
                    + max_strength_starting_with(ps, used_bits | (1u64 << i), *p),
            );
        }
    }
    unsafe {
        if result > ANS {
            ANS = result;
            eprintln!("{}", ANS)
        }
    }
    result
}

fn main() {
    let pairs: Vec<[u8; 2]> = io::stdin()
        .lock()
        .lines()
        .map(|line| decode_pair(&line.unwrap()))
        .collect();

    let (sources, segments): (Vec<_>, Vec<_>) = pairs.into_iter().partition(|ab| ab[0] == 0);

    for s in sources {
        println!("{:?}", max_strength_starting_with(&segments, 0, s));
    }
}
