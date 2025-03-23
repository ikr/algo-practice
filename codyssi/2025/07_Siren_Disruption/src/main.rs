use std::io::{self, BufRead};

fn parse_ipair(s: &str) -> (usize, usize) {
    let parts: Vec<usize> = s.split('-').map(|x| x.parse().unwrap()).collect();
    (parts[0] - 1, parts[1] - 1)
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap())
        .collect();

    let i_sep_a = lines.iter().position(|s| s.is_empty()).unwrap();
    let i_sep_b = lines.iter().rposition(|s| s.is_empty()).unwrap();

    let mut fs: Vec<u32> = lines[..i_sep_a]
        .iter()
        .map(|s| s.parse().unwrap())
        .collect();

    let ijs: Vec<_> = lines[i_sep_a + 1..i_sep_b]
        .iter()
        .map(|s| parse_ipair(s))
        .collect();

    for (i, j) in ijs {
        fs.swap(i, j);
    }

    let i0: usize = lines[i_sep_b + 1].parse::<usize>().unwrap() - 1;
    println!("{}", fs[i0]);
}
