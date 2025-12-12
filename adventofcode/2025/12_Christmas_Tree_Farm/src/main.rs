use itertools::Itertools;
use memoize::memoize;
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

    fn area(&self) -> usize {
        self.0
            .iter()
            .map(|row| row.iter().filter(|&&x| x).count())
            .sum()
    }

    fn height(&self) -> usize {
        self.0.len()
    }

    fn width(&self) -> usize {
        self.0[0].len()
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

    fn total_shapes_area(&self, shapes: &[Shape]) -> usize {
        self.shape_counts
            .iter()
            .zip(shapes)
            .map(|(count, shape)| count * shape.area())
            .sum()
    }

    fn empty_region(&self) -> Region {
        Region::new(self.height, self.width)
    }
}

#[derive(Clone, Eq, Hash, PartialEq)]
struct Region(Vec<Vec<bool>>);

impl Region {
    fn new(height: usize, width: usize) -> Self {
        Self(vec![vec![false; width]; height])
    }

    fn height(&self) -> usize {
        self.0.len()
    }

    fn width(&self) -> usize {
        self.0[0].len()
    }

    fn bit_blt(&self, shape: &Shape, ro: usize, co: usize) -> Option<Self> {
        let (sh, sw) = (shape.height(), shape.width());
        let mut xss = self.0.clone();

        for i in 0..sh {
            for j in 0..sw {
                if xss[ro + i][co + j] {
                    return None;
                }
                xss[ro + i][co + j] = true;
            }
        }

        Some(Self(xss))
    }
}

#[memoize(Ignore: shapes)]
fn fit_recur(shapes: &[Shape], region: Region, unused_shapes_counts: Vec<usize>) -> bool {
    if unused_shapes_counts.iter().all(|&x| x == 0) {
        true
    } else {
        let ks: Vec<usize> = (0..unused_shapes_counts.len())
            .filter(|&k| unused_shapes_counts[k] != 0)
            .collect();
        let ks_len = ks.len();

        ks.into_iter().permutations(ks_len).any(|pk| {
            pk.into_iter().any(|k| {
                shapes[k].all_configurations().into_iter().any(|cfg| {
                    let (sh, sw) = (cfg.height(), cfg.width());
                    let (h, w) = (region.height(), region.width());

                    for ro in 0..=h - sh {
                        for co in 0..=w - sw {
                            if let Some(next_region) = region.bit_blt(&cfg, ro, co) {
                                let mut next_counts = unused_shapes_counts.clone();
                                next_counts[k] -= 1;
                                eprintln!("{}\n", display_text('#', &next_region.0));

                                if fit_recur(shapes, next_region, next_counts) {
                                    return true;
                                }
                            }
                        }
                    }
                    false
                })
            })
        })
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
        eprintln!("{} -- {}\n", shape.display_text(), shape.area());
    }

    let initial_region_goals: Vec<RegionGoal> = paragraphs
        .last()
        .unwrap()
        .split('\n')
        .map(RegionGoal::decode)
        .collect();
    let initial_region_goals_count = initial_region_goals.len();
    eprintln!("Initial region goals count: {}", initial_region_goals_count);

    let region_goals: Vec<RegionGoal> = initial_region_goals
        .into_iter()
        .filter(|rg| rg.total_shapes_area(&shapes) <= rg.height * rg.width)
        .collect();
    eprintln!(
        "Removed {} obviously impossible goals",
        initial_region_goals_count - region_goals.len()
    );

    let result = region_goals
        .into_iter()
        .filter(|rg| {
            let result = fit_recur(&shapes, rg.empty_region(), rg.shape_counts.clone());
            eprint!(".");
            result
        })
        .count();
    eprintln!();
    println!("{result}");
}
