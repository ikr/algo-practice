const M: u64 = 26;
const Z: u8 = b'a';
const L: usize = 8;

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
        vec![b'a'; L]
    } else {
        let mut result = vec![];
        while x != 0 {
            result.push(Z + (x % M) as u8);
            x /= M;
        }
        while result.len() < L {
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

fn has_one_of_iol(xs: &[u8]) -> bool {
    xs.iter().any(|x| *x == b'i' || *x == b'o' || *x == b'l')
}

fn pair_indices(xs: &[u8]) -> Vec<usize> {
    xs.windows(2)
        .enumerate()
        .filter(|(_, xy)| if let [x, y] = xy { x == y } else { false })
        .map(|x| x.0)
        .collect()
}

fn has_at_least_two_non_overlapping_pairs(xs: &[u8]) -> bool {
    match pair_indices(xs)[..] {
        [a, .., b] => b - a > 1,
        _ => false,
    }
}

fn is_valid_password(xs: &[u8]) -> bool {
    has_straight_triple(xs) && !has_one_of_iol(xs) && has_at_least_two_non_overlapping_pairs(xs)
}

fn main() {
    let xs: Vec<u8> = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .as_bytes()
        .to_vec();

    let mut cur = xs.clone();
    loop {
        cur = word_of(word_value(&cur) + 1);
        if is_valid_password(&cur) {
            break;
        }
    }

    println!("{}", String::from_utf8(cur).unwrap());
}
