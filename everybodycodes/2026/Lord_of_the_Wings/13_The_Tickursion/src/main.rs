use proconio::input;

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
    eprintln!("degs:{degrees:?} dirs:{directions:?} curs:{current_values:?} movs:{moves:?}");
}
