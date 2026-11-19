use num_integer::lcm;
use proconio::input;

const EPS: f64 = 0.000_001;

fn time_to_meet_within_next_tick(m: i32, a1: i32, v1: i32, a2: i32, v2: i32) -> Option<f64> {
    if a1 == a2 || v1 == v2 {
        None
    } else {
        let [a1, a2] = [a1 as f64, a2 as f64];
        let [v1, v2] = [v1 as f64, v2 as f64];
        let m = m as f64;

        let q = v1 - v2;
        let p = a2 - a1;

        [(p - m) / q, p / q, (p + m) / q]
            .into_iter()
            .filter(|&x| x > 0.0)
            .min_by(f64::total_cmp)
            .filter(|&x| x < 1.0)
    }
}

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

fn main() {
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
    let directions: Vec<i32> = directions_source.split(":").map(decode_direction).collect();
    let current_values = decode_colon_sparated_ints(current_values_source);
    let moves = decode_colon_sparated_ints(moves_source);

    let m: i32 = degrees.iter().fold(1, |agg, &x| lcm(agg, x));
    let vs: Vec<i32> = degrees
        .into_iter()
        .zip(directions)
        .map(|(x, sgn)| sgn * (m / x))
        .collect();

    let xs: Vec<i32> = current_values
        .into_iter()
        .zip(vs.iter())
        .map(|(a, &v)| a * v.abs())
        .collect();

    eprintln!("m:{m} vs:{vs:?} xs:{xs:?}");
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_time_to_meet_within_next_tick() {
        let m = 12;
        for (a1, v1, a2, v2, expected) in [
            (1, 1, 1, 1, false),
            (11, 4, 1, 1, true),
            (1, 2, 9, 1, false),
            (1, 2, 4, 2, false),
            (1, 6, 3, 2, true),
        ] {
            let actual = time_to_meet_within_next_tick(m, a1, v1, a2, v2);

            assert_eq!(
                expected,
                actual.is_some(),
                "a1:{a1} v1:{v1} - a2:{a2} v2:{v2}"
            )
        }
    }
}
