use std::io::{BufRead, stdin};

#[derive(Clone, Debug)]
struct Machine {
    end_bits: u16,
    toggles: Vec<u16>,
}

impl Machine {
    fn decode_end_bits(s: &str) -> u16 {
        s.strip_prefix('[')
            .and_then(|s| s.strip_suffix(']'))
            .unwrap()
            .bytes()
            .enumerate()
            .filter_map(|(i, x)| if x == b'#' { Some(1 << i) } else { None })
            .fold(0u16, |acc, x| acc | x)
    }

    fn decode_button(s: &str) -> u16 {
        let offsets: Vec<usize> = s
            .strip_prefix('(')
            .and_then(|s| s.strip_suffix(')'))
            .unwrap()
            .split(',')
            .map(|sub| sub.parse().unwrap())
            .collect();

        offsets
            .into_iter()
            .map(|i| 1u16 << i)
            .fold(0u16, |acc, x| acc | x)
    }

    fn decode(s: &str) -> Self {
        let top_parts: Vec<_> = s.split(" {").collect();
        let pre_parts: Vec<_> = top_parts[0].split(' ').collect();
        let end_bits = Self::decode_end_bits(pre_parts[0]);
        let toggles = pre_parts[1..]
            .iter()
            .map(|&s| Self::decode_button(s))
            .collect();
        Self { end_bits, toggles }
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let machines: Vec<Machine> = lines.into_iter().map(|s| Machine::decode(&s)).collect();
    eprintln!("{:?}", machines);
}
