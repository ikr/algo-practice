use itertools::Itertools;
use std::{collections::HashSet, io::Read};

fn display_text(symbol: char, xss: &[Vec<bool>]) -> String {
    xss.iter()
        .map(|row| {
            row.iter()
                .map(|&x| if x { symbol } else { '.' })
                .collect::<String>()
        })
        .collect::<Vec<_>>()
        .join("\n")
}

fn transpose<T>(grid: Vec<Vec<T>>) -> Vec<Vec<T>> {
    assert!(!grid.is_empty());
    let h = grid[0].len();
    let mut iters: Vec<_> = grid.into_iter().map(|n| n.into_iter()).collect();
    (0..h)
        .map(|_| {
            iters
                .iter_mut()
                .map(|n| n.next().unwrap())
                .collect::<Vec<T>>()
        })
        .collect()
}

#[derive(Clone, Eq, Hash, PartialEq)]
struct Shape(Vec<Vec<bool>>);

impl Shape {
    fn decode_line(s: &str) -> Vec<bool> {
        s.chars().map(|x| x == '#').collect()
    }

    fn decode(s: &str) -> Self {
        Self(s.split('\n').skip(1).map(Self::decode_line).collect())
    }

    fn display_text(&self) -> String {
        display_text('#', &self.0)
    }

    fn flip(&self) -> Self {
        let xss: Vec<Vec<bool>> = self
            .0
            .iter()
            .map(|row| row.iter().rev().copied().collect())
            .collect();

        Self(xss)
    }

    fn transpose(&self) -> Self {
        Self(transpose(self.0.clone()))
    }

    fn rotate(&self) -> Self {
        self.transpose().flip()
    }

    fn all_configurations(&self) -> Vec<Self> {
        let mut result: HashSet<Self> = HashSet::new();

        for mut shape in [self.clone(), self.flip()] {
            result.insert(shape.clone());

            for _ in 0..3 {
                shape = shape.rotate();
                result.insert(shape.clone());
            }
        }

        result.into_iter().collect()
    }
}

#[derive(Debug)]
struct RegionGoal {
    height: usize,
    width: usize,
    shape_counts: Vec<usize>,
}

impl RegionGoal {
    fn decode(s: &str) -> Self {
        let (dimensions_src, counts_src) = s.split(": ").collect_tuple().unwrap();

        let (width, height) = dimensions_src
            .split('x')
            .map(|sub| sub.parse::<usize>().unwrap())
            .collect_tuple()
            .unwrap();

        let shape_counts: Vec<usize> = counts_src
            .split(' ')
            .map(|sub| sub.parse().unwrap())
            .collect();

        Self {
            height,
            width,
            shape_counts,
        }
    }
}

fn main() {
    let mut buf: String = String::new();
    std::io::stdin().read_to_string(&mut buf).unwrap();
    let paragraphs: Vec<_> = buf.trim_end().split("\n\n").collect();

    let shapes: Vec<Shape> = paragraphs
        .iter()
        .dropping_back(1)
        .map(|s| Shape::decode(s))
        .collect();

    for shape in &shapes {
        eprintln!("{}\n", shape.display_text());
    }

    let region_goals: Vec<RegionGoal> = paragraphs
        .last()
        .unwrap()
        .split('\n')
        .map(RegionGoal::decode)
        .collect();

    eprintln!("{:?}", region_goals);

    for shape in shapes.last().unwrap().all_configurations() {
        eprintln!("{}\n", shape.display_text());
    }
}
