use itertools::{Either, Itertools};
use std::{
    collections::{HashMap, VecDeque},
    io::{BufRead, stdin},
    iter::{once, successors},
};

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

    fn crd_of(&self, x: char) -> (usize, usize) {
        for (i, row) in self.xss.iter().enumerate() {
            for (j, &cell) in row.iter().enumerate() {
                if cell == x {
                    return (i, j);
                }
            }
        }
        unreachable!()
    }

    fn jth_column_reversed(&self, j: usize) -> Vec<char> {
        let n = self.xss[j].len();
        let mut result = vec![];
        let lo = if j.is_multiple_of(2) { 0 } else { 1 };

        for i in (lo..lo + 2 * n).step_by(2) {
            result.push(self.xss[i][j / 2]);
        }

        result.reverse();
        result
    }

    fn rotate(&self) -> Self {
        let mut xss = self.xss.clone();

        for (i, row) in xss.iter_mut().enumerate() {
            *row = self.jth_column_reversed(i);
        }

        Self { xss }
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let g0 = TriGrid::from_rectangular(lines);
    let gs: Vec<TriGrid> = successors(Some(g0), |g| Some(g.rotate())).take(3).collect();

    let src0 = gs[0].crd_of('S');
    let src = (0, src0.0, src0.1);

    let dst0 = gs[0].crd_of('E');
    let dst1 = gs[1].crd_of('E');
    let dst2 = gs[2].crd_of('E');

    let dsts = [
        (0, dst0.0, dst0.1),
        (1, dst1.0, dst1.1),
        (2, dst2.0, dst2.1),
    ];

    let mut distance: HashMap<(usize, usize, usize), usize> = HashMap::new();
    distance.insert(src, 0);
    let mut q: VecDeque<(usize, usize, usize)> = VecDeque::from([src]);

    while let Some(u) = q.pop_front() {
        let du: usize = *distance.get(&u).unwrap();
        let (k, u_ro, u_co) = u;
        let kk = (k + 1) % gs.len();

        for (v_ro, v_co) in gs[kk]
            .adjacent((u_ro, u_co))
            .into_iter()
            .chain(once((u_ro, u_co)))
            .filter(|&(i, j)| gs[kk].xss[i][j] != '#')
        {
            if !distance.contains_key(&(kk, v_ro, v_co)) {
                distance.insert((kk, v_ro, v_co), du + 1);
                q.push_back((kk, v_ro, v_co));
            }
        }
    }

    let result = dsts
        .into_iter()
        .map(|u| distance.get(&u).unwrap_or(&usize::MAX))
        .min()
        .unwrap();

    println!("{}", result);
}
