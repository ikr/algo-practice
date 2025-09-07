use std::io::{BufRead, stdin};

use itertools::Itertools;

struct Die {
    faces: Vec<i32>,
    seed: usize,
    pulse: usize,
    current_face_index: usize,
    roll_number: usize,
}

impl Die {
    fn new(faces: Vec<i32>, seed: usize) -> Self {
        Self {
            faces,
            seed,
            pulse: seed,
            current_face_index: 0,
            roll_number: 0,
        }
    }

    fn value(&self) -> i32 {
        self.faces[self.current_face_index]
    }

    fn roll(&mut self) {
        self.roll_number += 1;
        let spin = self.roll_number * self.pulse;

        self.current_face_index += spin;
        self.current_face_index %= self.faces.len();

        self.pulse += spin;
        self.pulse %= self.seed;
        self.pulse = self.pulse + 1 + self.roll_number + self.seed;
    }
}

fn extract_faces(input_line: &str) -> Vec<i32> {
    let csv = input_line.split(['[', ']']).nth(1).unwrap();
    csv.split(',').map(|s| s.parse().unwrap()).collect()
}

fn extract_seed(input_line: &str) -> usize {
    input_line.split('=').next_back().unwrap().parse().unwrap()
}

fn rolls_to_finish(race_track: &[i32], mut d: Die) -> usize {
    let mut i: usize = 0;
    while i != race_track.len() {
        d.roll();
        if race_track[i] == d.value() {
            i += 1;
        }
    }
    d.roll_number
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let isep = lines.iter().position(|s| s.is_empty()).unwrap();

    let dies: Vec<Die> = lines[..isep]
        .iter()
        .map(|line| Die::new(extract_faces(line), extract_seed(line)))
        .collect();

    let race_track: Vec<i32> = lines[isep + 1].bytes().map(|x| (x - b'0') as i32).collect();

    let rtf: Vec<_> = dies
        .into_iter()
        .map(|d| rolls_to_finish(&race_track, d))
        .collect();

    let answer = rtf
        .into_iter()
        .enumerate()
        .sorted_by_key(|(_, rs)| *rs)
        .map(|(i, _)| i + 1)
        .map(|k| k.to_string())
        .join(",");
    println!("{answer}");
}
