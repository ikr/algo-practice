use std::io::{BufRead, stdin};

const RLI: char = '\u{2067}';
const LRI: char = '\u{2066}';
const PDI: char = '\u{2069}';

fn remove_bidi_markers(s: &str) -> String {
    s.chars().filter(|c| ![RLI, LRI, PDI].contains(c)).collect()
}

fn run_length_encoding(xs: &[u8]) -> Vec<(u8, usize)> {
    let mut result: Vec<(u8, usize)> = vec![(xs[0], 1)];
    for &x in &xs[1..] {
        if x == result.last().unwrap().0 {
            result.last_mut().unwrap().1 += 1;
        } else {
            result.push((x, 1));
        }
    }
    result
}

fn rle_cumulative_size_at(rle: &[(u8, usize)], i: usize) -> usize {
    rle[..i].iter().map(|(_, k)| k).sum()
}

fn first_top_stretch_bounds(xs: &[u8]) -> (usize, usize) {
    let rle = run_length_encoding(xs);
    let hi: u8 = rle.iter().max_by_key(|(x, _)| x).unwrap().0;
    let rle_index = rle.iter().position(|(x, _)| *x == hi).unwrap();
    let i0 = rle_cumulative_size_at(&rle, rle_index);
    (i0, i0 + rle[rle_index].1)
}

fn apply_bidi_instructions(string_with_instruction_marker_chars: String) -> String {
    todo!()
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    eprintln!("{:?}", lines);
    assert!(lines.iter().all(|s| s.chars().count() < 256));

    let naive_lines: Vec<String> = lines.iter().map(|s| remove_bidi_markers(s)).collect();
    eprintln!("{:?}", naive_lines);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_first_top_stretch_bounds() {
        for (input, output) in [
            (vec![1], (0, 1)),
            (vec![1, 1, 1], (0, 3)),
            (vec![0, 1, 2, 2, 1, 1, 0], (2, 4)),
            (vec![0, 1, 1, 0, 1, 2, 1, 0], (5, 6)),
        ] {
            assert_eq!(first_top_stretch_bounds(&input), output);
        }
    }
}
