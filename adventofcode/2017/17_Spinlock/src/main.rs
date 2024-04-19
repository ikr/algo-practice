use indexset::BTreeMap;
use num_rational::Rational64;

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
    let mut buf: BTreeMap<Rational64, u32> =
        BTreeMap::from_iter([(Rational64::from(0), 0), (Rational64::from(1), 1)]);
    let mut i: usize = 1;
    let mut y: u32 = 0;
    for x in 2usize..=2017usize {
        i += jump_distance + 1;
        i %= x;

        let key = buf.get_index(i).unwrap().0;
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
