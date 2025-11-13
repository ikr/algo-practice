use itertools::Itertools;
use std::io::Read;

const N: usize = 8;

fn intersect(mut xs: [usize; 4]) -> bool {
    xs.sort();
    xs.iter().tuple_windows().any(|(x, y)| x == y)
}

fn chords_match(ab: (usize, usize), cd: (usize, usize)) -> bool {
    let mut xs = [ab.0, ab.1];
    xs.sort();
    let mut ys = [cd.0, cd.1];
    ys.sort();
    xs == ys
}

fn chords_knot(ab: (usize, usize), cd: (usize, usize)) -> bool {
    let (mut a, mut b) = ab;
    if a > b {
        (b, a) = (a, b);
    }

    let (c, d) = cd;

    if chords_match(ab, cd) {
        true
    } else if intersect([a, b, c, d]) {
        false
    } else {
        let is_rhs = |x: usize| -> bool { a < x && x < b };
        is_rhs(c) != is_rhs(d)
    }
}

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).unwrap();

    let xs: Vec<usize> = buf
        .trim()
        .split(',')
        .map(|x| x.to_string().parse().unwrap())
        .collect();

    let chords: Vec<(usize, usize)> = xs.into_iter().tuple_windows().collect();

    let result = (1..=N)
        .tuple_combinations()
        .map(|(a, b)| {
            let r = chords.iter().filter(|&&cd| chords_knot((a, b), cd)).count();
            eprintln!("{r} at {:?}", (a, b));
            r
        })
        .max()
        .unwrap();

    println!("{result}");
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_chords_not() {
        assert!(chords_knot((1, 5), (2, 6)));
        assert!(chords_knot((1, 5), (7, 3)));
        assert!(chords_knot((1, 5), (1, 5)));
        assert!(!chords_knot((8, 6), (1, 5)));
    }
}
