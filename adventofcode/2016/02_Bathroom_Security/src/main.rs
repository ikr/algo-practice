use std::io::{self, BufRead};

struct Numpad {
    grid: Vec<Vec<char>>,
    current_row: i8,
    current_col: i8,
}

impl Numpad {
    fn new() -> Numpad {
        Numpad {
            grid: vec![
                vec!['1', '2', '3'],
                vec!['4', '5', '6'],
                vec!['7', '8', '9'],
            ],
            current_row: 1,
            current_col: 1,
        }
    }

    fn move_once(&mut self, direction_code: char) {
        match direction_code {
            'U' => self.current_row -= 1,
            'R' => self.current_col += 1,
            'D' => self.current_row += 1,
            'L' => self.current_col -= 1,
            _ => panic!("Invalid direction code {}", direction_code),
        }
        self.current_row = self.current_row.clamp(0, 2);
        self.current_col = self.current_col.clamp(0, 2);
    }

    fn dial_digit(&mut self, direction_codes: &[char]) -> char {
        for c in direction_codes {
            self.move_once(*c);
        }
        self.grid[self.current_row as usize][self.current_col as usize]
    }
}

fn main() {
    let instruction_lines: Vec<Vec<char>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect::<Vec<char>>())
        .collect();

    let mut np = Numpad::new();
    let mut result = String::new();

    for line in instruction_lines{
        result.push(np.dial_digit(&line));
    }

    println!("{}", result);
}
