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

const SUFFIX: [u8; 5] = [17, 31, 73, 47, 23];

fn amend_lengths(xs: &[u8]) -> Vec<usize> {
    let mut result = xs.to_vec();
    result.extend(SUFFIX);
    result.into_iter().map(|x| x as usize).collect()
}

fn xor_compress(xs: &[u8]) -> Vec<u8> {
    let mut result: Vec<u8> = vec![];
    for ys in xs.chunks(16) {
        result.push(ys.iter().copied().reduce(|acc, y| acc ^ y).unwrap())
    }
    result
}

fn knot_hash(input: &str) -> Vec<u8> {
    let lengths = amend_lengths(&ascii_encode(input));
    let mut xs: Vec<u8> = (0..=255).collect();
    let mut i: usize = 0;
    let n = xs.len();
    let mut skip: usize = 0;

    for _ in 0..64 {
        for l in lengths.iter() {
            if *l > 0 {
                let j = (i + n + l - 1) % n;
                tricky_reverse(&mut xs, i, j);
            }
            i = (i + l + skip) % n;
            skip += 1
        }
    }

    xor_compress(&xs)
}

fn row_source(key: &str, row_index: u8) -> String {
    [key, &row_index.to_string()].join("-")
}

fn main() {
    let key: String = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .to_string();

    let row_hashes = (0..128)
        .into_iter()
        .map(|i| knot_hash(&row_source(&key, i)));
    let result1: u32 = row_hashes.into_iter().fold(0u32, |acc, xs| {
        acc + xs.iter().map(|x| x.count_ones()).sum::<u32>()
    });
    println!("{}", result1);
}
