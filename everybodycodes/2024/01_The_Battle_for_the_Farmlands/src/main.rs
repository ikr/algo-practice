use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).unwrap();

    let xs: Vec<u8> = buf.trim_end().as_bytes().to_vec();

    let result =
        xs.iter().filter(|&&x| x == b'B').count() + xs.iter().filter(|&&x| x == b'C').count() * 3;
    println!("{}", result);
}
