use std::io::Read;

const BLOCKS_SUPPLY: usize = 202520252025000;

fn is_wall_of_length_k_possible(spell: &[usize], num_blocks: usize, k: usize) -> bool {
    let mut r = num_blocks;

    for &d in spell {
        let layer = k / d;

        if r < layer {
            return false;
        }

        r -= layer;
    }

    true
}

fn max_wall_length(spell: Vec<usize>) -> usize {
    let mut lo: usize = 1;
    assert!(is_wall_of_length_k_possible(&spell, BLOCKS_SUPPLY, lo));
    let mut hi: usize = BLOCKS_SUPPLY;
    assert!(!is_wall_of_length_k_possible(&spell, BLOCKS_SUPPLY, hi));

    while lo + 1 != hi {
        let mid = lo + (hi - lo) / 2;
        if is_wall_of_length_k_possible(&spell, BLOCKS_SUPPLY, mid) {
            lo = mid;
        } else {
            hi = mid;
        }
    }

    lo
}

fn main() {
    let mut buf: String = String::new();
    std::io::stdin().read_to_string(&mut buf).unwrap();

    let mut xs: Vec<u8> = buf.trim().split(',').map(|s| s.parse().unwrap()).collect();
    let n = xs.len();
    let mut spell: Vec<usize> = vec![];

    while let Some(i0) = xs.iter().position(|&x| x != 0) {
        let d = i0 + 1;
        spell.push(d);

        for i in (i0..n).step_by(d) {
            assert_ne!(xs[i], 0);
            xs[i] -= 1;
        }
    }

    println!("{}", max_wall_length(spell));
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_is_wall_of_length_k_possible() {
        let spell = [1, 2, 3, 5, 9];
        for (b, k, expected) in [
            (1, 1, true),
            (1, 2, false),
            (10, 5, true),
            (10, 6, false),
            (100, 47, true),
            (202520252025000, 94439495762954, true),
        ] {
            assert_eq!(
                is_wall_of_length_k_possible(&spell, b, k),
                expected,
                "Expected {expected} on {:?}",
                (b, k)
            );
        }
    }
}
