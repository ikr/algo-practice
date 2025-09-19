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
    let mut xs: Vec<char> = string_with_instruction_marker_chars.chars().collect();
    let mut lv: Vec<u8> = vec![0; xs.len()];

    let mut current_level: u8 = 0;
    let mut digit_bump_active: bool = false;

    for (i, &x) in xs.iter().enumerate() {
        match x {
            RLI | LRI => {
                current_level += 1;
                digit_bump_active = false;
            }
            PDI => {
                current_level -= 1;
                digit_bump_active = false;
            }
            '0'..='9' if current_level % 2 == 1 => {
                current_level += 1;
                digit_bump_active = true;
            }
            _ if digit_bump_active => {
                current_level -= 1;
                digit_bump_active = false;
            }
            _ => digit_bump_active = false,
        }
        lv[i] = current_level;
    }

    eprintln!("{:?}", lv);
    let tmp = "00000000000000001112111121112111112111112222222222222344333343334332211000";
    let ys: Vec<u8> = tmp.bytes().map(|b| b - b'0').collect();
    assert_eq!(lv, ys);
    todo!()
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    eprintln!("{:?}", lines);
    assert!(lines.iter().all(|s| s.chars().count() < 256));

    let naive_lines: Vec<String> = lines.iter().map(|s| remove_bidi_markers(s)).collect();
    eprintln!("{:?}", naive_lines);

    apply_bidi_instructions(lines.last().unwrap().clone());
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
