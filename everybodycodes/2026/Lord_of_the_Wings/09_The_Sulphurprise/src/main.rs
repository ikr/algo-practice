use itertools::{
    EitherOrBoth::{Both, Left, Right},
    Itertools,
};
use std::{
    io::{BufRead, stdin},
    ops::{Add, Mul},
};

fn vjoin<T: Add<Output = T>>(xs: Vec<T>, ys: Vec<T>) -> Vec<T> {
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
    joints: usize,
}

impl Plant {
    fn new(growth: usize, limit: usize) -> Self {
        assert_eq!(growth % 2, 1);

        Self {
            growth,
            limit,
            branch_fqs: vec![],
            leaf_fqs: vec![1],
            joints: 0,
        }
    }

    fn growth_tick_leaf_return_fqs_and_joints(
        &self,
        leaf: usize,
    ) -> (Vec<usize>, Vec<usize>, usize) {
        assert!(leaf < self.growth);

        let mut branch_fqs: Vec<usize> = vec![0; self.growth];
        let mut leaf_fqs: Vec<usize> = vec![0; self.growth];
        let mut joints = 0;

        if leaf + 1 == self.growth {
            branch_fqs[self.growth / 2] = 1;
            leaf_fqs[self.growth / 2] = 1;
            leaf_fqs[1] += 1;
            joints = 1;
        } else {
            leaf_fqs[leaf + 1] = 1;
        }

        (branch_fqs, leaf_fqs, joints)
    }

    fn growth_tick_branch_return_fqs_and_joints(&self, branch: usize) -> (Vec<usize>, usize) {
        assert!(branch < self.growth);

        let mut fqs: Vec<usize> = vec![0; self.growth];
        let mut joints = 0;

        if branch + 1 == self.growth {
            fqs[self.growth / 2] = 2;
            fqs[1] += 1;
            joints = 1;
        } else {
            fqs[branch + 1] = 1;
        }

        (fqs, joints)
    }

    fn growth_tick(&mut self) {
        let leaf_branch_fqs: Vec<usize>;
        (leaf_branch_fqs, self.leaf_fqs, self.joints) = self.leaf_fqs.iter().enumerate().fold(
            (vec![], vec![], self.joints),
            |(bfqs, lfqs, joints), (l, &f)| {
                let (new_bfqs, new_lfqs, new_joints) =
                    self.growth_tick_leaf_return_fqs_and_joints(l);

                (
                    vjoin(bfqs, vscale(new_bfqs, f)),
                    vjoin(lfqs, vscale(new_lfqs, f)),
                    joints + new_joints * f,
                )
            },
        );

        (self.branch_fqs, self.joints) = self.branch_fqs.iter().enumerate().fold(
            (leaf_branch_fqs, self.joints),
            |(fqs, joints), (b, &f)| {
                let (new_fqs, new_joints) = self.growth_tick_branch_return_fqs_and_joints(b);

                (vjoin(fqs, vscale(new_fqs, f)), joints + new_joints * f)
            },
        )
    }

    fn simulate_return_growth_time(&mut self) -> usize {
        eprintln!("t:0 {self:?}");

        for t in 1..100_000 {
            self.growth_tick();
            eprintln!("t:{t} {self:?}");

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
