use std::{
    collections::{HashSet, VecDeque},
    io::{BufRead, stdin},
};

use itertools::Itertools;

const BASE: usize = 150;
const TARGET_RANK: u128 = 100000000000000000000000000000;

fn parse_main_staircase_end(s: &str) -> usize {
    let ps: Vec<_> = s.split(" : ").collect();
    assert_eq!(ps.len(), 3);

    let ab: Vec<usize> = ps[1].split(" -> ").map(|x| x.parse().unwrap()).collect();
    assert_eq!(ab.len(), 2);
    assert_eq!(ab[0], 0);

    ab[1]
}

#[derive(Clone, Copy, Debug)]
struct StaircaseBranch {
    id: usize,
    steps_range: (usize, usize),
    source_id: usize,
    destination_id: usize,
}

impl StaircaseBranch {
    fn parse_id(s: &str) -> usize {
        s.strip_prefix("S").unwrap().parse::<usize>().unwrap() - 1
    }

    fn parse_source_and_destination(s: &str) -> (usize, usize) {
        let ps: Vec<_> = s.split_whitespace().collect();
        assert_eq!(ps.len(), 4);
        (Self::parse_id(ps[1]), Self::parse_id(ps[3]))
    }

    fn parse(s: &str) -> Self {
        let ps: Vec<_> = s.split(" : ").collect();
        assert_eq!(ps.len(), 3);
        let id = Self::parse_id(ps[0]);

        let ab: Vec<usize> = ps[1].split(" -> ").map(|x| x.parse().unwrap()).collect();
        assert_eq!(ab.len(), 2);
        let steps_range = (ab[0], ab[1]);

        let (source_id, destination_id) = Self::parse_source_and_destination(ps[2]);
        Self {
            id,
            steps_range,
            source_id,
            destination_id,
        }
    }
}

fn valid_moves_recur(
    g: &[Vec<usize>],
    current_path: &[usize],
    remaining_magnitude: usize,
) -> HashSet<usize> {
    let u: usize = *current_path.last().unwrap();
    if remaining_magnitude == 0 {
        HashSet::from([u])
    } else {
        let mut result = HashSet::new();
        let mut p = current_path.to_vec();
        for &v in g[u].iter() {
            if !current_path.contains(&v) {
                p.push(v);
                result.extend(valid_moves_recur(g, &p, remaining_magnitude - 1));
                p.pop();
            }
        }
        result
    }
}

fn valid_moves(g: &[Vec<usize>], magnitudes: &[usize], u: usize) -> Vec<usize> {
    let result = magnitudes
        .iter()
        .fold(HashSet::new(), |mut acc, &m| {
            acc.extend(valid_moves_recur(g, &[u], m));
            acc
        })
        .into_iter()
        .collect();

    result
}

fn toposort(g: &[Vec<usize>]) -> Vec<usize> {
    let n = g.len();
    let mut indeg: Vec<usize> = vec![0; n];

    for vs in g.iter() {
        for &v in vs.iter() {
            indeg[v] += 1;
        }
    }

    let mut q: VecDeque<usize> = indeg
        .iter()
        .enumerate()
        .filter_map(|(u, &x)| if x == 0 { Some(u) } else { None })
        .collect();

    let mut result: Vec<usize> = vec![];
    while let Some(u) = q.pop_front() {
        result.push(u);
        for &v in g[u].iter() {
            indeg[v] -= 1;
            if indeg[v] == 0 {
                q.push_back(v);
            }
        }
    }
    result
}

fn vertex_code(vid: usize) -> String {
    let staricase_id = vid / BASE + 1;
    let step_id = vid % BASE;
    "S".to_string() + &staricase_id.to_string() + "_" + &step_id.to_string()
}

fn path_code(path: &[usize]) -> String {
    path.iter()
        .map(|&vid| vertex_code(vid))
        .collect::<Vec<_>>()
        .join("-")
}

fn vid(staircase_id: usize, step: usize) -> usize {
    staircase_id * BASE + step
}

fn path_counts(n: usize, gg: &[Vec<usize>], magnitudes: &[usize]) -> Vec<u128> {
    let us = toposort(gg);

    let mut dp: Vec<u128> = vec![0; BASE * BASE];
    dp[vid(0, n - 1)] = 1;

    for u in us {
        for v in valid_moves(gg, magnitudes, u) {
            dp[v] += dp[u];
        }
    }
    dp
}

fn staircases_graph(n: usize, branches: &[StaircaseBranch]) -> Vec<Vec<usize>> {
    let mut g: Vec<Vec<usize>> = vec![vec![]; BASE * BASE];

    for i in 1..n {
        g[vid(0, i - 1)].push(vid(0, i));
    }

    for b in branches {
        let (i, j) = b.steps_range;
        g[vid(b.source_id, i)].push(vid(b.id, i));

        for k in i..j {
            g[vid(b.id, k)].push(vid(b.id, k + 1));
        }

        g[vid(b.id, j)].push(vid(b.destination_id, j));
    }
    g
}

fn inverse_graph(g: &[Vec<usize>]) -> Vec<Vec<usize>> {
    let mut gg: Vec<Vec<usize>> = vec![vec![]; BASE * BASE];
    for (u, adj) in g.iter().enumerate() {
        for &v in adj.iter() {
            gg[v].push(u);
        }
    }
    gg
}

fn target_rank_path(n: usize, g: &[Vec<usize>], magnitudes: &[usize]) -> Vec<usize> {
    let dp = path_counts(n, &inverse_graph(g), magnitudes);
    let ua = vid(0, 0);
    let uz = vid(0, n - 1);

    let mut offset = 0u128;
    let mut result = vec![ua];

    while *result.last().unwrap() != uz {
        let u = *result.last().unwrap();
        for v in valid_moves(g, magnitudes, u).into_iter().sorted() {
            if offset + dp[v] < TARGET_RANK {
                offset += dp[v];
            } else {
                result.push(v);
                break;
            }
        }
    }

    result
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let n = parse_main_staircase_end(&lines[0]) + 1;
    let m = lines.len() - 2;

    let branches: Vec<StaircaseBranch> = lines[1..m]
        .iter()
        .map(|s| StaircaseBranch::parse(s))
        .collect();

    let magnitudes: Vec<usize> = lines
        .last()
        .and_then(|s| s.strip_prefix("Possible Moves : "))
        .unwrap()
        .split(", ")
        .map(|x| x.parse().unwrap())
        .collect();

    let g = staircases_graph(n, &branches);
    println!("{}", path_code(&target_rank_path(n, &g, &magnitudes)));
}
