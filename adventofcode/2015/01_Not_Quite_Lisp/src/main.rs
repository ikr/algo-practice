fn main() {
    let xs: Vec<u8> = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .to_owned()
        .into_bytes();

    let result1 = xs
        .iter()
        .fold(0, |acc, x| acc + if *x == b'(' { 1 } else { -1 });
    println!("{}", result1);

    let ss: Vec<i64> = xs
        .into_iter()
        .scan(0, |acc, x| {
            let delta = if x == b'(' { 1 } else { -1 };
            *acc += delta;
            Some(*acc)
        })
        .collect();

    let result2 = ss.into_iter().position(|x| x == -1).unwrap() + 1;
    println!("{}", result2);
}
