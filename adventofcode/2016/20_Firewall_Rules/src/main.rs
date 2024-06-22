use std::io::{self, BufRead};

fn are_touching(ab: (u32, u32), cd: (u32, u32)) -> bool {
    let (a, b) = ab;
    let (c, d) = cd;
    !(b < c || d < a) || (b != u32::MAX && b + 1 == c) || (d != u32::MAX && d + 1 == a)
}

fn union(ab: (u32, u32), cd: (u32, u32)) -> (u32, u32) {
    assert!(are_touching(ab, cd));
    let (a, b) = ab;
    let (c, d) = cd;
    let mut xs = [a, b, c, d];
    xs.sort();
    (xs[0], xs[3])
}

fn main() {
    let mut source_segments: Vec<(u32, u32)> = io::stdin()
        .lock()
        .lines()
        .map(|line| {
            let parts: Vec<String> = line.unwrap().split('-').map(|x| x.to_owned()).collect();
            assert_eq!(parts.len(), 2);
            (parts[0].parse().unwrap(), parts[1].parse().unwrap())
        })
        .collect();
    source_segments.sort_by_key(|(_, x)| *x);

    let mut segments: Vec<(u32, u32)> = vec![];
    while let Some(ab) = source_segments.pop() {
        let mut cur = ab;
        while let Some(cd) = source_segments.last() {
            if are_touching(*cd, cur) {
                cur = union(*cd, cur);
                source_segments.pop();
            } else {
                break;
            }
        }
        segments.push(cur);
    }
    segments.reverse();

    eprintln!("{:?}", segments);
    println!("{}", segments[0].1 + 1);
}
