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

fn solve_part_1(input: &str) -> u32 {
    let lengths: Vec<usize> = input.split(',').map(|x| x.parse().unwrap()).collect();

    let mut xs: Vec<u8> = (0..=255).collect();
    let mut i: usize = 0;
    let n = xs.len();

    for (skip, l) in lengths.into_iter().enumerate() {
        if l > 0 {
            let j = (i + n + l - 1) % n;
            tricky_reverse(&mut xs, i, j);
        }
        i = (i + l + skip) % n;
    }

    xs[0] as u32 * xs[1] as u32
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
        result.push(ys.to_vec().into_iter().reduce(|acc, y| acc ^ y).unwrap())
    }
    result
}

fn solve_part_2(input: &str) -> String {
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

    hexify(&xor_compress(&xs))
}

fn main() {
    let input: String = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .to_string();

    println!("{}", solve_part_1(&input));
    println!("{}", solve_part_2(&input));
}
