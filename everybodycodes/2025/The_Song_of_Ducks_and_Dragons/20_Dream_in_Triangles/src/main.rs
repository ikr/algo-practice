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
        if ro % 2 == 0 {
            if ro != 0 {
                result.push((ro - 1, co));
            }
            if co != 0 {
                result.push((ro + 1, co - 1));
            }
            if co != self.xss[ro].len() - 1 {
                result.push((ro + 1, co));
            }
        } else {
            result.extend([(ro - 1, co), (ro - 1, co + 1), (ro + 1, co)]);
        }
        result
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let g = TriGrid::from_rectangular(lines);
    let mut result = 0;

    for (i, row) in g.xss.iter().enumerate() {
        for (j, &cell) in row.iter().enumerate() {
            if cell == 'T' {
                result += g
                    .adjacent((i, j))
                    .into_iter()
                    .filter(|&(ii, jj)| i < ii && g.xss[ii][jj] == 'T')
                    .count();
            }
        }
    }

    println!("{result}");
}
