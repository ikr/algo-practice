use std::io::Read;

fn main() {
    let mut buf: String = String::new();
    std::io::stdin().read_to_string(&mut buf).unwrap();

    let mut xs: Vec<u8> = buf.trim().split(',').map(|s| s.parse().unwrap()).collect();
    let n = xs.len();
    let mut result: usize = 1;

    while let Some(i0) = xs.iter().position(|&x| x != 0) {
        let d = i0 + 1;
        result *= d;

        for i in (i0..n).step_by(d) {
            assert_ne!(xs[i], 0);
            xs[i] -= 1;
        }
    }

    println!("{result}");
}
