use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).unwrap();

    let mut csv: Vec<u32> = buf.trim().split(',').map(|s| s.parse().unwrap()).collect();
    eprintln!("{:?}", csv);
    csv.sort();
    csv.dedup();
    let n = csv.len();
    let result: u32 = csv[..20].into_iter().sum();
    println!("{result}");
}
