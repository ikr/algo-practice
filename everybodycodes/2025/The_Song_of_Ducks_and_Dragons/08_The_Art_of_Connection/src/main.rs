use itertools::Itertools;
use std::io::Read;

fn intersect(mut xs: [usize; 4]) -> bool {
    xs.sort();
    xs.iter().tuple_windows().any(|(x, y)| x == y)
}

fn chords_knot(ab: (usize, usize), cd: (usize, usize)) -> bool {
    let (mut a, mut b) = ab;
    if a > b {
        (b, a) = (a, b);
    }

    let (c, d) = cd;

    if intersect([a, b, c, d]) {
        return false;
    }

    let is_rhs = |x: usize| -> bool { a < x && x < b };
    is_rhs(c) != is_rhs(d)
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
    let mut result = 0;

    for (i, &ab) in chords.iter().enumerate() {
        result += chords[..i]
            .iter()
            .filter(|&&cd| chords_knot(ab, cd))
            .count();
    }

    println!("{result}");
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_chords_not() {
        assert!(chords_knot((1, 5), (2, 6)));
        assert!(chords_knot((1, 5), (7, 3)));
        assert!(!chords_knot((8, 6), (1, 5)));
    }
}
