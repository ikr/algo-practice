const M: u64 = 26;
const Z: u8 = b'a';

fn word_value(xs: &[u8]) -> u64 {
    let mut m: u64 = 1;
    let mut result: u64 = 0;
    for d in xs.iter().rev() {
        result += m * (d - Z) as u64;
        m *= M;
    }
    result
}

fn word_of(mut x: u64) -> Vec<u8> {
    if x == 0 {
        vec![b'a'; 8]
    } else {
        let mut result = vec![];
        while x != 0 {
            result.push(Z + (x % M) as u8);
            x /= M;
        }
        while result.len() < 8 {
            result.push(Z);
        }
        result.reverse();
        result
    }
}

fn has_straight_triple(xs: &[u8]) -> bool {
    xs.windows(3).any(|abc| {
        let [a, b, c] = abc else {
            panic!("{:?} isn't a triple", abc)
        };
        *a + 1 == *b && *b + 1 == *c
    })
}

fn main() {
    let xs: Vec<u8> = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .as_bytes()
        .to_vec();

    assert_eq!(xs, word_of(word_value(&xs)));
}
