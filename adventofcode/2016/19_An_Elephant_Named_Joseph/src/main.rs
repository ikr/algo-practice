use indexset::BTreeSet;

fn next_key(circle: &BTreeSet<usize>, k: usize) -> usize {
    assert!(circle.len() >= 2);
    if k == *circle.last().unwrap() {
        *circle.iter().next().unwrap()
    } else {
        *circle.range(k + 1..).next().unwrap()
    }
}

fn opposite_key(circle: &BTreeSet<usize>, k: usize) -> usize {
    let n = circle.len();
    assert!(n >= 2);
    let i = circle.rank(&k);
    let j = (i + n / 2) % n;
    *circle.get_index(j).unwrap()
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
        let q = opposite_key(&circle, k);
        circle.remove(&q);

        if circle.len() > 1 {
            k = next_key(&circle, k);
        }
    }

    println!("{}", circle.iter().next().unwrap())
}
