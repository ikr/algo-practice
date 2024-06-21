use std::collections::BTreeSet;

fn next_key(circle: &BTreeSet<usize>, k: usize) -> usize {
    assert!(circle.len() >= 2);
    if k == *circle.last().unwrap() {
        *circle.iter().next().unwrap()
    } else {
        *circle.range(k + 1..).next().unwrap()
    }
}

fn main() {
    let n: usize = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .parse()
        .unwrap();

    let mut circle: BTreeSet<usize> = (1..=n).collect();

    let mut k: usize = 1;
    while circle.len() > 1 {
        assert!(circle.contains(&k));
        let q = next_key(&circle, k);
        circle.remove(&q);

        if circle.len() > 1 {
            k = next_key(&circle, k);
        }
    }

    println!("{}", circle.iter().next().unwrap())
}
