use std::collections::BTreeMap;

fn next_key(circle: &BTreeMap<usize, usize>, k: usize) -> usize {
    assert!(circle.len() >= 2);
    if k == *circle.keys().last().unwrap() {
        *circle.keys().next().unwrap()
    } else {
        *circle.range(k + 1..).next().unwrap().0
    }
}

fn main() {
    let n: usize = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .parse()
        .unwrap();

    let mut circle: BTreeMap<usize, usize> = (1..=n).map(|i| (i, 1)).collect();

    let mut k: usize = 1;
    while circle.len() > 1 {
        assert!(circle.contains_key(&k));
        let q = next_key(&circle, k);
        let v = *circle.get(&q).unwrap();

        circle.entry(k).and_modify(|u| *u += v);
        circle.remove(&q);

        if circle.len() > 1 {
            k = next_key(&circle, k);
        }
    }

    println!("{}", circle.keys().next().unwrap())
}
