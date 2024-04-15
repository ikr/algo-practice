use std::collections::VecDeque;

const AZ: &str = "abcdefghijklmnopqrstuvwxyz";

fn initial_buffer(len: usize) -> VecDeque<char> {
    assert!(len <= AZ.len());
    AZ.chars().take(len).collect()
}

fn as_string(buf: &VecDeque<char>) -> String {
    buf.iter().collect()
}

fn slashed_pair(src: &str) -> (String, String) {
    let xs: Vec<&str> = src.split('/').collect();
    assert!(xs.len() == 2);
    (xs[0].to_string(), xs[1].to_string())
}

fn slashed_ints(src: &str) -> (usize, usize) {
    let (a, b) = slashed_pair(src);
    (a.parse().unwrap(), b.parse().unwrap())
}

fn slashed_chars(src: &str) -> (char, char) {
    let (a, b) = slashed_pair(src);
    assert!(a.len() == 1);
    assert!(b.len() == 1);
    (a.chars().next().unwrap(), b.chars().next().unwrap())
}

enum Operation {
    Spin(usize),
    Exchange(usize, usize),
    Partner(char, char),
}

impl Operation {
    fn decode(src: &str) -> Operation {
        match src.chars().next().unwrap() {
            's' => Operation::Spin(src[1..].parse().unwrap()),
            'x' => {
                let (a, b) = slashed_ints(&src[1..]);
                Operation::Exchange(a, b)
            }
            'p' => {
                let (a, b) = slashed_chars(&src[1..]);
                Operation::Partner(a, b)
            }
            _ => panic!("Unknown operation source {}", src),
        }
    }
}

fn main() {
    let ops: Vec<Operation> = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim_end()
        .split(',')
        .map(Operation::decode)
        .collect();

    let mut buf = initial_buffer(16);

    for op in ops {
        match op {
            Operation::Spin(i) => buf.rotate_right(i),
            Operation::Exchange(i, j) => buf.swap(i, j),
            Operation::Partner(a, b) => {
                let i = buf.iter().position(|x| *x == a).unwrap();
                let j = buf.iter().position(|x| *x == b).unwrap();
                buf.swap(i, j);
            }
        }
    }

    println!("{}", as_string(&buf));
}
