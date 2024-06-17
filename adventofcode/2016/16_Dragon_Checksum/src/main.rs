fn flip(xs: Vec<u8>) -> Vec<u8> {
    xs.into_iter()
        .map(|x| if x == b'0' { b'1' } else { b'0' })
        .collect()
}

fn grow(mut a: Vec<u8>) -> Vec<u8> {
    let b: Vec<u8> = flip(a.iter().copied().rev().collect());
    a.push(b'0');
    a.extend(b);
    a
}

fn fill(disk_size: usize, initial_state: &str) -> Vec<u8> {
    let mut xs: Vec<u8> = initial_state.as_bytes().to_vec();
    while xs.len() < disk_size {
        xs = grow(xs);
    }
    xs.into_iter().take(disk_size).collect()
}

fn checksum_round(xs: Vec<u8>) -> Vec<u8> {
    assert!(xs.len() % 2 == 0);
    xs.chunks(2)
        .map(|ab| {
            let [a, b] = ab else {
                panic!("{:?} isn't a pair", ab)
            };
            if a == b {
                b'1'
            } else {
                b'0'
            }
        })
        .collect()
}

fn checksum(mut xs: Vec<u8>) -> Vec<u8> {
    while xs.len() % 2 == 0 {
        xs = checksum_round(xs);
    }
    xs
}

fn solve(disk_size: usize, initial_state: &str) -> String {
    let xs = fill(disk_size, initial_state);
    String::from_utf8(checksum(xs)).unwrap()
}

fn main() {
    println!("{}", solve(12, "110010110100"));
    println!("{}", solve(20, "10000"));
    println!("{}", solve(272, "11100010111110100"));
}
