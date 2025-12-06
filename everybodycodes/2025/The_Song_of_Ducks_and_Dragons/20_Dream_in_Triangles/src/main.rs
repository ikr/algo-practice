use itertools::{Either, Itertools};
use std::io::{BufRead, stdin};

#[derive(Debug)]
struct TriGrid {
    xss: Vec<Vec<char>>,
}

impl TriGrid {
    fn from_rectangular(lines: Vec<String>) -> Self {
        let xss: Vec<Vec<char>> = lines
            .into_iter()
            .map(|s| s.trim_matches('.').to_string())
            .flat_map(|s| -> Vec<Vec<char>> {
                let (a, b) = s.chars().enumerate().partition_map(|(i, x)| {
                    if i % 2 == 0 {
                        Either::Left(x)
                    } else {
                        Either::Right(x)
                    }
                });

                vec![a, b]
            })
            .filter(|xs| !xs.is_empty())
            .collect();

        Self { xss }
    }

    fn adjacent(&self, crd: (usize, usize)) -> Vec<(usize, usize)> {
        let (ro, co) = crd;
        assert!(ro < self.xss.len());
        assert!(co < self.xss[ro].len());

        let mut result = vec![];
        todo!();
        result
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let g = TriGrid::from_rectangular(lines);
    eprintln!("{:?}", g);
}
