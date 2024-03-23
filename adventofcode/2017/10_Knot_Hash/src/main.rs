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

    for (skip, l) in lengths.iter().enumerate() {
        if *l > 0 {
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

const SUFFIX: [usize; 5] = [17, 31, 73, 47, 23];

fn amend_lengths(xs: &[usize]) -> Vec<usize> {
    let mut result = xs.to_vec();
    result.extend(SUFFIX);
    result
}

fn solve_part_2(input: &str) -> String {
    eprintln!("{:?}", ascii_encode("1,2,3"));
    todo!()
}

fn main() {
    let input: String = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .to_string();

    println!("{}", solve_part_1(&input));
    println!("{}", solve_part_2(&input));
}
