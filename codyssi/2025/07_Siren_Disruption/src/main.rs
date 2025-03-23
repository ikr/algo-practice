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
    let n = fs.len();

    let ijs: Vec<_> = lines[i_sep_a + 1..i_sep_b]
        .iter()
        .map(|s| parse_ipair(s))
        .collect();

    for (i0, j0) in ijs {
        let i = i0.min(j0);
        let j = i0.max(j0);
        assert_ne!(i, j);

        let m = (j - i).min(n - j);
        let mut a: Vec<u32> = fs[..i].to_vec();

        let b: Vec<u32> = fs[i..i + m].to_vec();
        let infix: Vec<u32> = fs[i + m..j].to_vec();
        let c: Vec<u32> = fs[j..j + m].to_vec();
        let suffix: Vec<u32> = fs[j + m..].to_vec();

        a.extend(c);
        a.extend(infix);
        a.extend(b);
        a.extend(suffix);

        fs = a;
    }

    let i0: usize = lines[i_sep_b + 1].parse::<usize>().unwrap() - 1;
    println!("{}", fs[i0]);
}
