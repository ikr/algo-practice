use std::collections::HashMap;
use std::ops::Add;

#[derive(Clone, Copy, PartialEq, Eq, Hash, Debug)]
struct Coord(i64, i64);

impl Add for Coord {
    type Output = Coord;

    fn add(self, other: Coord) -> Coord {
        Coord(self.0 + other.0, self.1 + other.1)
    }
}

fn containing_diameter(n: i64) -> i64 {
    let sqr = (n as f64).sqrt() as i64;
    let mut result = sqr - 2;
    while result < 0 || result % 2 == 0 || result * result < n {
        result += 1;
    }
    result
}

fn lowest_on_perimeter(d: i64) -> i64 {
    assert!(d > 0 && d % 2 == 1);
    if d == 1 {
        1
    } else {
        (d - 2) * (d - 2) + 1
    }
}

fn steps_to_access_port(n: i64) -> i64 {
    if n == 1 {
        0
    } else {
        let d = containing_diameter(n);
        let lo = lowest_on_perimeter(d);
        let nn = (n - lo) % (d - 1);

        assert!((d - 1) % 2 == 0);
        let side_center = (d - 1) / 2 - 1;
        d / 2 + (nn - side_center).abs()
    }
}

fn sum_of_adjacent_values(space: &HashMap<Coord, i64>, coord: Coord) -> i64 {
    let mut sum = 0;
    for dx in -1..=1 {
        for dy in -1..=1 {
            if dx == 0 && dy == 0 {
                continue;
            }
            let adjacent_coord = coord + Coord(dx, dy);
            if let Some(&value) = space.get(&adjacent_coord) {
                sum += value;
            }
        }
    }
    sum
}

fn is_a_squared_odd(n: i64) -> bool {
    assert!(n > 0);
    if n == 1 {
        return true;
    }
    let base = (n as f64).sqrt() as i64;
    for i in -2..=2 {
        if base + i > 0 && (base + i) * (base + i) == n && (base + i) % 2 == 1 {
            return true;
        }
    }
    false
}

fn delta_for(side: i64) -> Coord {
    match side {
        0 => Coord(0, 1),
        1 => Coord(-1, 0),
        2 => Coord(0, -1),
        3 => Coord(1, 0),
        _ => panic!("Invalid side: {}", side),
    }
}

fn next_step_delta(n: i64) -> Coord {
    assert!(n > 1);
    if is_a_squared_odd(n) {
        Coord(1, 0)
    } else {
        let d = containing_diameter(n);
        assert!(d - 1 >= 2);
        assert!((d - 1) % 2 == 0);
        let lo = lowest_on_perimeter(d);
        let side = (n - lo) / (d - 1);
        assert!(0 <= side && side < 4);
        let nn = (n - lo) % (d - 1);

        eprintln!("n={} d={} lo={} side={} nn={}", n, d, lo, side, nn);

        if nn == d - 2 {
            delta_for((side + 1) % 4)
        } else {
            delta_for(side)
        }
    }
}

fn first_summed_value_larger_than_n(n: i64) -> i64 {
    let mut space: HashMap<Coord, i64> = HashMap::new();
    let mut seq: i64 = 1;
    let mut coord = Coord(0, 0);
    space.insert(coord, seq);
    loop {
        seq += 1;
        coord = coord + next_step_delta(seq);
        let value = sum_of_adjacent_values(&space, coord);
        eprintln!("{}: {:?} -> {}", seq, coord, value);
        if value > n {
            return value;
        }
        space.insert(coord, value);
    }
}

fn main() {
    let n: i64 = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .parse()
        .unwrap();
    println!("{}", steps_to_access_port(n));
    println!("{}", first_summed_value_larger_than_n(n));
}
