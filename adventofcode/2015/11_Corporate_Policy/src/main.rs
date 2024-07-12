const M: u64 = 27;

fn word_value(xs: &[u8]) -> u64 {
    let mut m: u64 = 1;
    let mut result: u64 = 0;
    for d in xs.iter().rev() {
        result += m * (d - b'`') as u64;
        m *= M;
    }
    result
}

fn main() {
    let xs: String = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .to_owned();

    eprintln!("{}", word_value(xs.as_bytes()));
}
