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

struct Plant {
    growth: usize,
    limit: usize,
    branch_length_fqs: Vec<usize>,
    num_joints: usize,
}

impl Plant {
    fn new(growth: usize, limit: usize) -> Self {
        Self {
            growth,
            limit,
            branch_length_fqs: vec![1],
            num_joints: 0,
        }
    }

    fn growth_tick_one_return_fqs_and_joints(&self, branch: usize) -> (Vec<usize>, usize) {
        assert_eq!(self.growth % 2, 1);
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
        (self.branch_length_fqs, self.num_joints) = self.branch_length_fqs.iter().enumerate().fold(
            (vec![], self.num_joints),
            |(fqs, joints), (b, &f)| {
                let (new_singe_fqs, new_single_joints) =
                    self.growth_tick_one_return_fqs_and_joints(b);

                (
                    vjoin(fqs, vscale(new_singe_fqs, f)),
                    joints + new_single_joints * f,
                )
            },
        )
    }

    fn simulate_return_growth_time(&mut self) -> usize {
        for t in 1..1_000_000 {
            self.growth_tick();

            let total_branches_length: usize = self
                .branch_length_fqs
                .iter()
                .enumerate()
                .map(|(b, f)| b * f)
                .sum();

            let m = total_branches_length + self.num_joints;
            if m >= self.limit {
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
