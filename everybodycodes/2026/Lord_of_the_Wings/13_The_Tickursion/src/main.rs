use itertools::Itertools;
use num_integer::lcm;
use proconio::{input, is_stdin_empty};

fn decode_colon_sparated_ints(s: String) -> [i32; 3] {
    s.split(':')
        .map(|a| a.parse().unwrap())
        .collect::<Vec<_>>()
        .try_into()
        .unwrap()
}

fn decode_direction(s: &str) -> i32 {
    match s {
        "CW" => 1,
        "CCW" => -1,
        _ => unreachable!(),
    }
}

fn time_to_meet_before_next_tick(m: i32, x1: i32, v1: i32, x2: i32, v2: i32) -> Option<f64> {
    if x1 == x2 || v1 == v2 {
        None
    } else {
        let [x1, x2] = [x1 as f64, x2 as f64];
        let [v1, v2] = [v1 as f64, v2 as f64];
        let m = m as f64;

        let q = v1 - v2;
        let p = x2 - x1;

        [(p - m) / q, p / q, (p + m) / q]
            .into_iter()
            .filter(|&x| x > 0.0)
            .min_by(f64::total_cmp)
            .filter(|&x| x < 1.0)
    }
}

fn calubration_value(
    degrees: [i32; 3],
    directions: [i32; 3],
    initial_values: [i32; 3],
    mut moves: [i32; 3],
) -> i32 {
    let n = moves.len();
    let m: i32 = degrees.iter().fold(1, |agg, &x| lcm(agg, x));
    let mut vs: Vec<i32> = degrees
        .into_iter()
        .zip(directions)
        .map(|(x, sgn)| sgn * (m / x))
        .collect();

    let mut xs: Vec<i32> = initial_values
        .into_iter()
        .zip(vs.iter())
        .map(|(a, &v)| a * v.abs())
        .collect();

    for i in 0..n {
        if moves[i] == 0 {
            vs[i] = 0;
        }
    }

    let mut result = 0;

    while moves.iter().any(|&k| k > 0) {
        for [i, j] in (0..n).array_combinations() {
            if time_to_meet_before_next_tick(m, xs[i], vs[i], xs[j], vs[j]).is_some() {
                result += 1;
            }
        }

        for i in 0..n {
            xs[i] += vs[i] + m;
            xs[i] %= m;
            moves[i] = (moves[i] - 1).max(0);
        }

        if vs.iter().all(|&v| v != 0) && xs.iter().unique().count() == 1 {
            result += 3;
        } else {
            for [i, j] in (0..n).array_combinations() {
                if (vs[i] != 0 || vs[j] != 0) && xs[i] == xs[j] {
                    result += 1;
                }
            }
        }

        for i in 0..n {
            if moves[i] == 0 {
                vs[i] = 0;
            }
        }
    }

    result
}

fn main() {
    let mut result = 0;
    let mut i = 1;

    while !is_stdin_empty() {
        input! {
            _hands: String,
            degrees_source: String,
            _direction: String,
            directions_source: String,
            _current: String,
            current_values_source: String,
            _move: String,
            moves_source: String,
        }

        let degrees = decode_colon_sparated_ints(degrees_source);

        let directions: [i32; 3] = directions_source
            .split(":")
            .map(decode_direction)
            .collect::<Vec<_>>()
            .try_into()
            .unwrap();

        let initial_values = decode_colon_sparated_ints(current_values_source);
        let moves = decode_colon_sparated_ints(moves_source);
        let sub = calubration_value(degrees, directions, initial_values, moves);
        eprintln!("Clock {:03}: {sub}", i);
        result += sub;
        i += 1;
    }

    println!("{result}");
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_time_to_meet_within_next_tick() {
        let m = 12;
        for (x1, v1, x2, v2, expected) in [
            (1, 1, 1, 1, false),
            (11, 4, 1, 1, true),
            (1, 2, 9, 1, false),
            (1, 2, 4, 2, false),
            (1, 6, 3, 2, true),
        ] {
            let actual = time_to_meet_before_next_tick(m, x1, v1, x2, v2);

            assert_eq!(
                expected,
                actual.is_some(),
                "x1:{x1} v1:{v1} - x2:{x2} v2:{v2}"
            )
        }
    }
}
