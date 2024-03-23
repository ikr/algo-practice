fn tricky_reverse(xs: &mut [usize], mut i: usize, mut j: usize) {
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

fn solve_part_1(input: &str) -> usize {
    let lengths: Vec<usize> = input.split(',').map(|x| x.parse().unwrap()).collect();

    let mut xs: Vec<usize> = (0..256).collect();
    let mut i: usize = 0;
    let n = xs.len();

    for (skip, l) in lengths.iter().enumerate() {
        if *l > 0 {
            let j = (i + n + l - 1) % n;
            tricky_reverse(&mut xs, i, j);
        }
        i = (i + l + skip) % n;
    }

    xs[0] * xs[1]
}

fn solve_part_2(input: &str) -> String {
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
