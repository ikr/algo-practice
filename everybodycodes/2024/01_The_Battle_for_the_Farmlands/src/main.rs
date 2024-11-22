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

fn potions_for_tri(mut pqr: [u8; 3]) -> usize {
    pqr.sort();
    match pqr {
        [b'x', b'x', b'x'] => 0,
        [p, b'x', b'x'] => potions_for_one(p),
        [p, q, b'x'] => potions_for_one(p) + potions_for_one(q) + 2,
        [p, q, r] => potions_for_one(p) + potions_for_one(q) + potions_for_one(r) + 6,
    }
}

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).unwrap();

    let xss: Vec<(u8, u8, u8)> = buf
        .trim_end()
        .as_bytes()
        .chunks(3)
        .map(|ys| (ys[0], ys[1], ys[2]))
        .collect();

    let result: usize = xss
        .into_iter()
        .map(|(p, q, r)| potions_for_tri([p, q, r]))
        .sum();
    println!("{}", result);
}
