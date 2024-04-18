fn main() {
    let jump_distance: usize = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .parse()
        .unwrap();

    let mut buf: Vec<usize> = vec![0, 1];
    let mut i: usize = 1;

    for x in 2usize..=2017usize {
        i += jump_distance + 1;
        i %= x;
        if i == 0 {
            i = x;
        }
        buf.insert(i, x);
        let y = buf[(i + 1) % buf.len()];
        eprintln!("{} added at {}; next to the right is {}", x, i, y);
    }
}
