use std::collections::HashMap;

fn hash(salt: &str, x: usize) -> String {
    let mut result = format!("{:x}", md5::compute(salt.to_owned() + &x.to_string()));
    for _ in 0..2016 {
        result = format!("{:x}", md5::compute(result));
    }
    result
}

fn is_one_value_repeated<T>(xs: &[T]) -> Option<T>
where
    T: Copy + PartialEq + std::fmt::Debug,
{
    if let Some(a) = xs.first() {
        if xs.iter().all(|x| x == a) {
            Some(*a)
        } else {
            None
        }
    } else {
        panic!("No elements in {:?}", xs);
    }
}

fn all_repeated(xs: &str, repeats: usize) -> Vec<char> {
    xs.chars()
        .collect::<Vec<_>>()
        .windows(repeats)
        .fold(vec![], |mut acc, ys| {
            if let Some(a) = is_one_value_repeated(ys) {
                acc.push(a);
            }
            acc
        })
}

fn main() {
    let salt: String = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .to_owned();

    let mut tris: Vec<(char, usize)> = vec![];
    let mut idx5: HashMap<char, Vec<usize>> = HashMap::new();

    for i in 0..32_000 {
        let h = hash(&salt, i);
        if let Some(c) = all_repeated(&h, 3).first() {
            tris.push((*c, i));
        }
        for c in all_repeated(&h, 5) {
            idx5.entry(c).and_modify(|ii| ii.push(i)).or_insert(vec![i]);
        }
    }

    let key_indices = tris
        .into_iter()
        .filter(|(c, x0)| {
            if let Some(xs) = idx5.get(c) {
                let i = xs.partition_point(|x| x <= x0);
                if i != xs.len() {
                    assert!(xs[i] > *x0);
                }
                i < xs.len() && xs[i] - x0 < 1000
            } else {
                false
            }
        })
        .collect::<Vec<_>>();

    eprintln!("{:?}", key_indices);

    println!("{}", key_indices[63].1);
}
