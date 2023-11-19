use std::io::{self, BufRead};

const AZ: usize = (b'z' - b'a' + 1) as usize;
type Freqs = [i32; AZ];

fn read_input() -> Vec<String> {
    let mut xs = Vec::new();
    for line in io::stdin().lock().lines() {
        xs.push(String::from(line.unwrap().trim()));
    }
    xs
}

fn letter_frequences(xs: &str) -> Freqs {
    let mut freqs = [0; AZ];
    for c in xs.bytes() {
        freqs[usize::from(c - b'a')] += 1;
    }
    freqs
}

fn count_occurances(xs: &Freqs, value: i32) -> i32 {
    xs.iter().filter(|&&x| x == value).count() as i32
}

fn main() {
    let xs = read_input();
    let fs = xs.iter().map(|x| letter_frequences(x)).collect::<Vec<_>>();

    let mut twos = 0;
    let mut threes = 0;
    for f in fs {
        if count_occurances(&f, 2) > 0 {
            twos += 1;
        }
        if count_occurances(&f, 3) > 0 {
            threes += 1;
        }
    }

    println!("{}", twos * threes);
}
