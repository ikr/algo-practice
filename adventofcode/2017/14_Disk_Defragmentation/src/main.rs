fn tricky_reverse(xs: &mut [u8], mut i: usize, mut j: usize) {
    let n = xs.len();
    while i != j {
        xs.swap(i, j);
        i = (i + 1) % n;
        if i == j {
            break;
        }
        j = (j + n - 1) % n;
    }
}

fn ascii_encode(input: &str) -> Vec<u8> {
    input.chars().map(|c| c as u8).collect()
}

fn hex_of(a: u8) -> String {
    format!("{:02x}", a)
}

fn hexify(a: &[u8]) -> String {
    let v: Vec<String> = a.iter().map(|x| hex_of(*x)).collect();
    v.join("")
}

fn xor_compress(xs: &[u8]) -> Vec<u8> {
    let mut result: Vec<u8> = vec![];
    for ys in xs.chunks(16) {
        result.push(ys.iter().copied().reduce(|acc, y| acc ^ y).unwrap())
    }
    result
}

fn knot_hash(input: &str) -> String {
    let lengths = ascii_encode(input);
    let mut xs: Vec<u8> = (0..=255).collect();
    let mut i: usize = 0;
    let n = xs.len();
    let mut skip: usize = 0;

    for _ in 0..64 {
        for l in lengths.iter().map(|x| *x as usize) {
            if l > 0 {
                let j = (i + n + l - 1) % n;
                tricky_reverse(&mut xs, i, j);
            }
            i = (i + l + skip) % n;
            skip += 1
        }
    }

    hexify(&xor_compress(&xs))
}

fn main() {
    let input: String = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .to_string();
    eprintln!("{}", knot_hash(&input));
}
