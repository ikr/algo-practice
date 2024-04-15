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
    (a.chars().nth(0).unwrap(), b.chars().nth(0).unwrap())
}

#[derive(Clone, Copy, Debug)]
enum Operation {
    Spin(usize),
    Exchange(usize, usize),
    Partner(char, char),
}

impl Operation {
    fn decode(src: &str) -> Operation {
        match src.chars().nth(0).unwrap() {
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
    let buf = initial_buffer(5);
    eprintln!("{:?}", buf);
    eprintln!("{:?}", as_string(&buf));

    let command_sources: Vec<String> = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim_end()
        .split(',')
        .map(|x| x.to_string())
        .collect();

    eprintln!("{:?}", command_sources);

    for src in command_sources {
        eprintln!("{:?}", Operation::decode(&src));
    }
}
