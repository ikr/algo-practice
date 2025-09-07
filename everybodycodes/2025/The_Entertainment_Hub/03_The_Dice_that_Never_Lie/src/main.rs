use std::io::{BufRead, stdin};

#[derive(Debug)]
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

    fn preview_next_spin(&self) -> usize {
        (self.roll_number + 1) * self.pulse
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
    input_line.split('=').last().unwrap().parse().unwrap()
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    for line in lines {
        let xs = extract_faces(&line);
        let s = extract_seed(&line);

        let mut d = Die::new(xs, s);
        eprintln!("{:?}", d);

        for _ in 0..100 {
            let spin = d.preview_next_spin();
            d.roll();

            let result = d.value();
            let pulse_after_roll = d.pulse;

            let roll_number = d.roll_number;
            eprintln!("{roll_number}\t{spin}\t{result}\t{pulse_after_roll}");
        }
    }
}
