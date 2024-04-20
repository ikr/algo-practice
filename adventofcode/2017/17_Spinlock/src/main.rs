use indexset::BTreeMap;
use num_bigint::BigInt;
use num_rational::BigRational;

fn solve_part_1(jump_distance: usize) -> usize {
    let mut buf: Vec<usize> = vec![0, 1];
    let mut i: usize = 1;
    let mut y: usize = 0;
    for x in 2usize..=2017usize {
        i += jump_distance + 1;
        i %= x;
        buf.insert(i, x);
        y = buf[(i + 1) % buf.len()];
    }
    y
}

fn solve_part_2(jump_distance: usize) -> u32 {
    let mut buf: BTreeMap<BigRational, u32> = BTreeMap::from_iter([
        (BigRational::from(BigInt::from(1_000_000)), 0),
        (BigRational::from(BigInt::from(1_000_000_000)), 1),
    ]);
    let mut i: usize = 1;
    let mut y: u32 = 1;
    for x in 2u32..=50000000u32 {
        i += jump_distance + 1;
        i %= x as usize;
        assert!(x as usize == buf.len());

        let key_b: BigRational = buf.get_index(i).unwrap().0.clone();
        let key_a: BigRational = if i == 0 {
            &key_b - BigInt::from(1_000_000)
        } else {
            buf.get_index(i - 1).unwrap().0.clone()
        };

        if x % 100_000 == 0 {
            eprintln!("{}", x);
        }

        buf.insert((key_a + key_b) / BigRational::from(BigInt::from(2)), x);
        let n = buf.len();
        if *buf.get_index((i + n - 1) % n).unwrap().1 == 0 {
            y = x
        };
    }
    y
}

fn main() {
    let jump_distance: usize = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .parse()
        .unwrap();
    println!("{}", solve_part_1(jump_distance));
    println!("{}", solve_part_2(jump_distance));
}
