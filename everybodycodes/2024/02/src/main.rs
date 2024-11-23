use std::{
    collections::HashSet,
    io::{self, BufRead},
};

fn reversed(s: &[u8]) -> Vec<u8> {
    let mut xs = s.to_vec();
    xs.reverse();
    xs
}

fn bimatch_indices(haystack: &[u8], needle: &[u8]) -> HashSet<usize> {
    let needle_reversed = reversed(needle);
    let n = haystack.len();
    let m = needle.len();

    let mut result: HashSet<usize> = HashSet::new();

    for i in 0..=(n - m) {
        let window = &haystack[i..(i + m)];
        if window == needle || window == needle_reversed {
            for j in i..(i + m) {
                result.insert(j);
            }
        }
    }

    result
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap())
        .collect();

    let words: Vec<String> = lines[0]
        .strip_prefix("WORDS:")
        .unwrap()
        .split(',')
        .map(|s| s.trim().to_string())
        .collect();

    let mut result: usize = 0;

    for line in lines[2..].iter() {
        let idx = words.iter().fold(HashSet::new(), |acc, word| {
            acc.union(&bimatch_indices(line.as_bytes(), word.as_bytes()))
                .cloned()
                .collect()
        });

        result += idx.len();
    }

    println!("{}", result);
}
