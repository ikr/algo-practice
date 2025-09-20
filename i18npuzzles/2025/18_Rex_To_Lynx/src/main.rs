use std::io::{BufRead, stdin};

const RLI: char = '\u{2067}';
const LRI: char = '\u{2066}';
const PDI: char = '\u{2069}';

#[derive(Clone, Copy)]
enum BidiMarker {
    Rli,
    Lri,
    Pdi,
}

impl BidiMarker {
    fn from(x: char) -> Option<Self> {
        match x {
            RLI => Some(Self::Rli),
            LRI => Some(Self::Lri),
            PDI => Some(Self::Pdi),
            _ => None,
        }
    }

    fn all() -> Vec<Self> {
        vec![Self::Rli, Self::Lri, Self::Pdi]
    }

    fn index(self) -> usize {
        match self {
            Self::Rli => 0,
            Self::Lri => 1,
            Self::Pdi => 2,
        }
    }
}

struct BidiMarkersIndex {
    idx: Vec<Vec<usize>>,
}

impl BidiMarkersIndex {
    fn marker_on(&self, i: usize) -> Option<BidiMarker> {
        BidiMarker::all()
            .into_iter()
            .find(|bm| self.idx[bm.index()].contains(&i))
    }
}

fn externalize_bidi_markers(
    string_with_instruction_marker_chars: String,
) -> (Vec<char>, BidiMarkersIndex) {
    let mut idx = vec![vec![]; BidiMarker::all().len()];
    let mut xs: Vec<char> = vec![];

    for x in string_with_instruction_marker_chars.chars() {
        if let Some(bm) = BidiMarker::from(x) {
            idx[bm.index()].push(xs.len());
        } else {
            xs.push(x);
        }
    }

    (xs, BidiMarkersIndex { idx })
}

fn remove_bidi_markers(s: &str) -> String {
    s.chars()
        .filter(|&c| BidiMarker::from(c).is_none())
        .collect()
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
    let (mut xs, idx) = externalize_bidi_markers(string_with_instruction_marker_chars);
    let mut lv: Vec<u8> = vec![0; xs.len()];

    let mut current_level: u8 = 0;
    let mut digit_bump_active: bool = false;

    for (i, &x) in xs.iter().enumerate() {
        match idx.marker_on(i) {
            Some(BidiMarker::Rli | BidiMarker::Lri) => {
                current_level += 1;
                digit_bump_active = false;
            }
            Some(BidiMarker::Pdi) => {
                current_level -= 1;
                digit_bump_active = false;
            }
            _ if x.is_ascii_digit() && current_level % 2 == 1 => {
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
    let tmp = "00000000000000011121111211121111121111222222222222344333343334332100";
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
