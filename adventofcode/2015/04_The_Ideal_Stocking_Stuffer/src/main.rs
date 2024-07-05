use std::process::exit;

fn hash(key: &str, x: i32) -> String {
    format!("{:x}", md5::compute(key.to_owned() + &x.to_string()))
}

fn k_zeros(k: usize) -> String {
    String::from_utf8(vec![b'0'; k]).unwrap()
}

fn main() {
    let key: String = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .to_owned();

    let pat = k_zeros(5);
    for x in 0..100_000_000 {
        let h = hash(&key, x);
        if h.starts_with(&pat) {
            println!("{}", x);
            exit(0);
        }
    }
}
