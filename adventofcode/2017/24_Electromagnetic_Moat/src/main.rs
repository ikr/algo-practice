use std::io::{self, BufRead};

fn decode_pair(src: &str) -> [u8; 2] {
    let mut result: Vec<u8> = src.split('/').map(|part| part.parse().unwrap()).collect();
    result.sort();
    result.try_into().unwrap()
}

fn other_than(p: &[u8], x: u8) -> u8 {
    assert!(p.len() == 2);
    if p[0] == x {
        p[1]
    } else {
        p[0]
    }
}

fn max_strength_starting_with(ps: &[[u8; 2]], used_bits: u64, a0: u8, b0: u8) -> (u8, u16) {
    let mut result_length = used_bits.count_ones() as u8;
    let mut result_weight = (a0 + b0) as u16;

    for (i, p) in ps.iter().enumerate() {
        if (1u64 << i) & used_bits == 0u64 && p.contains(&b0) {
            let a1 = b0;
            let b1 = other_than(p, a1);

            let sub = max_strength_starting_with(ps, used_bits | (1u64 << i), a1, b1);
            if sub.0 > result_length
                || (sub.0 == result_length && (a0 + b0) as u16 + sub.1 > result_weight)
            {
                result_length = sub.0;
                result_weight = (a0 + b0) as u16 + sub.1
            }
        }
    }
    (result_length, result_weight)
}

fn main() {
    let pairs: Vec<[u8; 2]> = io::stdin()
        .lock()
        .lines()
        .map(|line| decode_pair(&line.unwrap()))
        .collect();

    let (sources, segments): (Vec<_>, Vec<_>) = pairs.into_iter().partition(|ab| ab[0] == 0);

    for s in sources {
        println!("{:?}", max_strength_starting_with(&segments, 0, s[0], s[1]));
    }
}
