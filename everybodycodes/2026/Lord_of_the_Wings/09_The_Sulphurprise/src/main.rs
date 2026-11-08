use itertools::{
    EitherOrBoth::{Both, Left, Right},
    Itertools,
};
use std::{
    io::{BufRead, stdin},
    ops::{Add, Mul},
};

fn vmerge<T: Add<Output = T>>(xs: Vec<T>, ys: Vec<T>) -> Vec<T> {
    xs.into_iter()
        .zip_longest(ys)
        .map(|xy| match xy {
            Both(x, y) => x + y,
            Left(a) | Right(a) => a,
        })
        .collect()
}

fn vscale<T: Mul<Output = T> + Copy>(xs: Vec<T>, k: T) -> Vec<T> {
    xs.into_iter().map(|x| x * k).collect()
}

#[derive(Debug)]
struct Plant {
    growth: usize,
    limit: usize,
    branch_fqs: Vec<usize>,
    leaf_fqs: Vec<usize>,
}

impl Plant {
    fn new(growth: usize, limit: usize) -> Self {
        assert_eq!(growth % 2, 1);

        Self {
            growth,
            limit,
            branch_fqs: vec![],
            leaf_fqs: vec![1],
        }
    }

    fn growth_tick_leaf_return_fqs(&self, leaf: usize) -> (Vec<usize>, Vec<usize>) {
        assert!(leaf < self.growth);

        let mut branch_fqs: Vec<usize> = vec![0; self.growth];
        let mut leaf_fqs: Vec<usize> = vec![0; self.growth];

        if leaf + 1 == self.growth {
            branch_fqs[self.growth / 2] = 1;
            leaf_fqs[self.growth / 2] = 1;
            leaf_fqs[1] += 1;
        } else {
            leaf_fqs[leaf + 1] = 1;
        }

        (branch_fqs, leaf_fqs)
    }

    fn growth_tick_branch_return_fqs(&self, branch: usize) -> (Vec<usize>, Vec<usize>) {
        assert!(branch < self.growth);

        let mut branch_fqs: Vec<usize> = vec![0; self.growth];
        let mut leaf_fqs: Vec<usize> = vec![0; self.growth];

        if branch + 1 == self.growth {
            branch_fqs[self.growth / 2] = 2;
            leaf_fqs[1] = 1;
        } else {
            branch_fqs[branch + 1] = 1;
        }

        (branch_fqs, leaf_fqs)
    }

    fn growth_tick(&mut self) {
        let leaf_branch_fqs: Vec<usize>;
        (leaf_branch_fqs, self.leaf_fqs) =
            self.leaf_fqs
                .iter()
                .enumerate()
                .fold((vec![], vec![]), |(bfqs, lfqs), (l, &f)| {
                    let (new_bfqs, new_lfqs) = self.growth_tick_leaf_return_fqs(l);

                    (
                        vmerge(bfqs, vscale(new_bfqs, f)),
                        vmerge(lfqs, vscale(new_lfqs, f)),
                    )
                });

        (self.branch_fqs, self.leaf_fqs) = self.branch_fqs.iter().enumerate().fold(
            (leaf_branch_fqs, self.leaf_fqs.clone()),
            |(bfqs, lfqs), (b, &f)| {
                let (new_bfqs, new_lfqs) = self.growth_tick_branch_return_fqs(b);

                (
                    vmerge(bfqs, vscale(new_bfqs, f)),
                    vmerge(lfqs, vscale(new_lfqs, f)),
                )
            },
        )
    }

    fn simulate_return_growth_time(&mut self) -> usize {
        for t in 1..100_000 {
            self.growth_tick();

            if self.leaf_fqs.iter().copied().sum::<usize>() >= self.limit {
                return t;
            }
        }

        unreachable!()
    }
}

fn decode_prefixed_int(s: &str, prefix: &str) -> usize {
    s.strip_prefix(prefix).unwrap().parse().unwrap()
}

fn decode_plant(s: String) -> Plant {
    let (_, growth_src, limit_src) = s.split(", ").collect_tuple().unwrap();

    Plant::new(
        decode_prefixed_int(growth_src, "growth="),
        decode_prefixed_int(limit_src, "limit="),
    )
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let ps: Vec<_> = lines.into_iter().map(decode_plant).collect();

    let result: Vec<_> = ps
        .into_iter()
        .map(|mut p| p.simulate_return_growth_time())
        .collect();

    eprintln!("{result:?}");
    println!("{}", result.into_iter().sum::<usize>());
}
