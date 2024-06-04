use std::collections::HashMap;
use std::io::{self, BufRead};

struct Numpad {
    graph: HashMap<(char, char), char>,
    current: char,
}

impl Numpad {
    fn new() -> Numpad {
        Numpad {
            graph: HashMap::from([
                (('1', 'U'), '1'),
                (('1', 'R'), '1'),
                (('1', 'D'), '3'),
                (('1', 'L'), '1'),
                (('2', 'U'), '2'),
                (('2', 'R'), '3'),
                (('2', 'D'), '6'),
                (('2', 'L'), '2'),
                (('3', 'U'), '1'),
                (('3', 'R'), '4'),
                (('3', 'D'), '7'),
                (('3', 'L'), '2'),
                (('4', 'U'), '4'),
                (('4', 'R'), '4'),
                (('4', 'D'), '8'),
                (('4', 'L'), '3'),
                (('5', 'U'), '5'),
                (('5', 'R'), '6'),
                (('5', 'D'), '5'),
                (('5', 'L'), '5'),
                (('6', 'U'), '2'),
                (('6', 'R'), '7'),
                (('6', 'D'), 'A'),
                (('6', 'L'), '5'),
                (('7', 'U'), '3'),
                (('7', 'R'), '8'),
                (('7', 'D'), 'B'),
                (('7', 'L'), '6'),
                (('8', 'U'), '4'),
                (('8', 'R'), '9'),
                (('8', 'D'), 'C'),
                (('8', 'L'), '7'),
                (('9', 'U'), '9'),
                (('9', 'R'), '9'),
                (('9', 'D'), '9'),
                (('9', 'L'), '8'),
                (('A', 'U'), '6'),
                (('A', 'R'), 'B'),
                (('A', 'D'), 'A'),
                (('A', 'L'), 'A'),
                (('B', 'U'), '7'),
                (('B', 'R'), 'C'),
                (('B', 'D'), 'D'),
                (('B', 'L'), 'A'),
                (('C', 'U'), '8'),
                (('C', 'R'), 'C'),
                (('C', 'D'), 'C'),
                (('C', 'L'), 'B'),
                (('D', 'U'), 'B'),
                (('D', 'R'), 'D'),
                (('D', 'D'), 'D'),
                (('D', 'L'), 'D'),
            ]),
            current: '5',
        }
    }

    fn move_once(&mut self, direction_code: char) {
        self.current = *self.graph.get(&(self.current, direction_code)).unwrap()
    }

    fn dial_digit(&mut self, direction_codes: &[char]) -> char {
        for c in direction_codes {
            self.move_once(*c);
        }
        self.current
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

    for line in instruction_lines {
        result.push(np.dial_digit(&line));
    }

    println!("{}", result);
}
