#[derive(Debug)]
enum Turn {
    L,
    R,
}

#[derive(Debug)]
struct Walk(i32);

#[derive(Debug)]
struct Hop(Turn, Walk);

fn decode_hop(src: &str) -> Hop {
    Hop(
        match src.chars().next().unwrap() {
            'L' => Turn::L,
            'R' => Turn::R,
            _ => panic!("Invalid turn direction in {}", src),
        },
        Walk(src[1..].parse().unwrap()),
    )
}

fn main() {
    let hops: Vec<Hop> = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim_end()
        .split(", ")
        .map(decode_hop)
        .collect();
    eprintln!("{:?}", hops);
}
