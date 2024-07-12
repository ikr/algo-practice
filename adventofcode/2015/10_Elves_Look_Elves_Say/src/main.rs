fn run_length_encoding(xs: &str) -> Vec<(usize, u8)> {
    assert!(!xs.is_empty());
    let mut result: Vec<(usize, u8)> = vec![(1, *xs.as_bytes().first().unwrap())];
    for x in xs.as_bytes().iter().skip(1) {
        if *x == result.last().unwrap().1 {
            result.last_mut().unwrap().0 += 1;
        } else {
            result.push((1, *x));
        }
    }
    result
}

fn look_and_say(rle: &[(usize, u8)]) -> String {
    rle.iter().fold("".to_owned(), |mut acc, (f, c)| {
        acc += &f.to_string();
        acc += &String::from_utf8(vec![*c]).unwrap();
        acc
    })
}

fn main() {
    let xs: String = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .to_owned();

    let result = (1..=50).fold(xs, |acc, _| look_and_say(&run_length_encoding(&acc)));
    println!("{}", result.len());
}
