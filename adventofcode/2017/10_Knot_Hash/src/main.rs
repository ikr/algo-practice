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

fn main() {
    let lengths: Vec<usize> = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .split(',')
        .map(|x| x.parse().unwrap())
        .collect();

    let mut xs: Vec<usize> = (0..256).collect();
    let mut i: usize = 0;
    let mut skip: usize = 0;
    let n = xs.len();

    for l in lengths {
        let j = (i + n + l - 1) % n;
        tricky_reverse(&mut xs, i, j);
        i = (i + l + skip) % n;
        skip += 1;
    }

    println!("{}", xs[0] * xs[1]);
}
