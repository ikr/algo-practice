use std::{
    collections::HashSet,
    io::{BufRead, stdin},
};

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

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let n = parse_main_staircase_end(&lines[0]) + 1;
    let m = lines.len() - 2;
    let base = n.max(m);

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

    let vid = |staircase_id: usize, step: usize| -> usize { staircase_id * base + step };
    let mut g: Vec<Vec<usize>> = vec![vec![]; base * base];

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

    let mut dp: Vec<u128> = vec![0; base * base];
    dp[vid(0, 0)] = 1;

    let mut dq: Vec<u128> = vec![0; base * base];

    loop {
        for (u, &x) in dp.iter().enumerate() {
            if x != 0 {
                for v in valid_moves(&g, &magnitudes, u) {
                    dq[v] += x;
                }
            }
        }

        eprintln!("{:?}\n{:?}\n\n", dp, dq);

        if dq == dp {
            break;
        }

        dp = dq;
        dq = vec![0; base * base];
    }

    println!("{}", dp[vid(0, n - 1)]);
}
