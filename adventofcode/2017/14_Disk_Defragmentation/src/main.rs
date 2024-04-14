use ac_library::Dsu;

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

fn is_nth_bit_set(row: &[u8], n: u8) -> bool {
    let byte_index = n as usize / 8;
    let bit_index = n % 8;
    row[byte_index] & (1u8 << bit_index) != 0
}

fn is_set_at(raster: &[Vec<u8>], ro: u8, co: u8) -> bool {
    is_nth_bit_set(&raster[ro as usize], co)
}

fn vertex_code(ro: u8, co: u8) -> usize {
    ro as usize * 128 + co as usize
}

fn main() {
    let key: String = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .to_string();

    let row_hashes: Vec<Vec<u8>> = (0..128).map(|i| knot_hash(&row_source(&key, i))).collect();
    let result1 = row_hashes.iter().fold(0, |acc, xs| {
        acc + xs.iter().map(|x| x.count_ones()).sum::<u32>()
    });
    println!("{}", result1);

    let mut dsu = Dsu::new(128 * 128);
    for ro in 0..128 {
        for co in 0..128 {
            if ro > 0 && is_set_at(&row_hashes, ro - 1, co) {
                dsu.merge(vertex_code(ro, co), vertex_code(ro - 1, co));
            }
            if co > 0 && is_set_at(&row_hashes, ro, co - 1) {
                dsu.merge(vertex_code(ro, co), vertex_code(ro, co - 1));
            }
            if ro < 127 && is_set_at(&row_hashes, ro + 1, co) {
                dsu.merge(vertex_code(ro, co), vertex_code(ro + 1, co));
            }
            if co < 127 && is_set_at(&row_hashes, ro, co + 1) {
                dsu.merge(vertex_code(ro, co), vertex_code(ro, co + 1));
            }
        }
    }
    let result2 = dsu.groups().len();
    println!("{}", result2);
}
