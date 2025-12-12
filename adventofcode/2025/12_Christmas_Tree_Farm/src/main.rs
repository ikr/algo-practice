use std::io::Read;

fn main() {
    let mut buf: String = String::new();
    std::io::stdin().read_to_string(&mut buf).unwrap();
    let blocks: Vec<_> = buf.split("\n\n").collect();
    eprintln!("{:?}", blocks);
}
