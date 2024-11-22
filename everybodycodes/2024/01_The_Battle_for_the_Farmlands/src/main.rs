use std::io::Read;

fn potions_for_one(x: u8) -> usize {
    match x {
        b'A' => 0,
        b'B' => 1,
        b'C' => 3,
        b'D' => 5,
        _ => panic!("Unknown unit {}", x),
    }
}

fn potions_for_pair(pq: (u8, u8)) -> usize {
    match pq {
        (b'x', b'x') => 0,
        (b'x', q) => potions_for_one(q),
        (p, b'x') => potions_for_one(p),
        (p, q) => potions_for_one(p) + potions_for_one(q) + 2,
    }
}

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).unwrap();

    let xss: Vec<(u8, u8)> = buf
        .trim_end()
        .as_bytes()
        .chunks(2)
        .map(|ys| (ys[0], ys[1]))
        .collect();

    let result: usize = xss.into_iter().map(potions_for_pair).sum();
    println!("{}", result);
}
