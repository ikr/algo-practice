use std::{
    collections::BTreeSet,
    io::{self, BufRead},
};

fn are_touching(ab: (u32, u32), cd: (u32, u32)) -> bool {
    let (a, b) = ab;
    let (c, d) = cd;
    !(b < c || d < a) || b + 1 == c || d + 1 == a
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
    let pairs: Vec<(u32, u32)> = io::stdin()
        .lock()
        .lines()
        .map(|line| {
            let parts: Vec<String> = line.unwrap().split('-').map(|x| x.to_owned()).collect();
            assert_eq!(parts.len(), 2);
            (parts[0].parse().unwrap(), parts[1].parse().unwrap())
        })
        .collect();

    let mut blocked: BTreeSet<(u32, u32)> = BTreeSet::new();
    for (a, b) in pairs {
        if let Some(cd) = blocked.range(..=(a, a)).last().copied() {
            if are_touching(cd, (a, b)) {
                blocked.remove(&cd);
                let ab_prime = union(cd, (a, b));

                if let Some(pq) = blocked.range((a, a)..).next().copied() {
                    if are_touching(ab_prime, pq) {
                        blocked.remove(&pq);
                        blocked.insert(union(ab_prime, pq));
                    } else {
                        blocked.insert(ab_prime);
                    }
                } else {
                    blocked.insert(ab_prime);
                }
            } else {
            }
        } else {
        }
    }
}
