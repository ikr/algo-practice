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

fn solve(disk_size: usize, initial_state: &str) -> String {
    String::from("TODO")
}

fn main() {
    println!("{}", solve(12, "110010110100"));
    println!("{}", solve(20, "10000"));
    println!("{}", solve(272, "11100010111110100"));

    assert_eq!(grow(vec![b'1']), vec![b'1', b'0', b'0']);
}
