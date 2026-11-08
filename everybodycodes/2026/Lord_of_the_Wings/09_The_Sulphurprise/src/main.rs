use itertools::Itertools;
use std::{
    collections::BTreeMap,
    io::{BufRead, stdin},
    ops::{AddAssign, Mul},
};

type Freqs = BTreeMap<usize, usize>;

fn mmerge<T: AddAssign + Copy + Ord>(xs: BTreeMap<T, T>, ys: BTreeMap<T, T>) -> BTreeMap<T, T> {
    xs.into_iter().fold(ys, |mut agg, (i, x)| {
        agg.entry(i).and_modify(|y| *y += x).or_insert(x);
        agg
    })
}

fn mscale<T: Mul<Output = T> + Copy + Ord>(xs: BTreeMap<T, T>, k: T) -> BTreeMap<T, T> {
    xs.into_iter().map(|(i, x)| (i, x * k)).collect()
}

struct Plant {
    growth: usize,
    limit: usize,
    branch_fqs: Freqs,
    leaf_fqs: Freqs,
}

impl Plant {
    fn new(growth: usize, limit: usize) -> Self {
        assert_eq!(growth % 2, 1);

        Self {
            growth,
            limit,
            branch_fqs: BTreeMap::new(),
            leaf_fqs: BTreeMap::from([(0, 1)]),
        }
    }

    fn growth_tick_leaf_return_fqs(&self, leaf: usize) -> (Freqs, Freqs) {
        assert!(leaf < self.growth);

        let mut branch_fqs = Freqs::new();
        let mut leaf_fqs = Freqs::new();

        if leaf + 1 == self.growth {
            branch_fqs.insert(self.growth / 2, 1);
            leaf_fqs.insert(self.growth / 2, 1);
            leaf_fqs.entry(1).and_modify(|f| *f += 1).or_insert(1);
        } else {
            leaf_fqs.insert(leaf + 1, 1);
        }

        (branch_fqs, leaf_fqs)
    }

    fn growth_tick_branch_return_fqs(&self, branch: usize) -> (Freqs, Freqs) {
        assert!(branch < self.growth);

        let mut branch_fqs = Freqs::new();
        let mut leaf_fqs = Freqs::new();

        if branch + 1 == self.growth {
            branch_fqs.insert(self.growth / 2, 2);
            leaf_fqs.insert(1, 1);
        } else {
            branch_fqs.insert(branch + 1, 1);
        }

        (branch_fqs, leaf_fqs)
    }

    fn growth_tick(&mut self) {
        let leaf_branch_fqs: Freqs;
        (leaf_branch_fqs, self.leaf_fqs) =
            self.leaf_fqs
                .iter()
                .fold((Freqs::new(), Freqs::new()), |(bfqs, lfqs), (&l, &f)| {
                    let (new_bfqs, new_lfqs) = self.growth_tick_leaf_return_fqs(l);

                    (
                        mmerge(bfqs, mscale(new_bfqs, f)),
                        mmerge(lfqs, mscale(new_lfqs, f)),
                    )
                });

        (self.branch_fqs, self.leaf_fqs) = self.branch_fqs.iter().fold(
            (leaf_branch_fqs, self.leaf_fqs.clone()),
            |(bfqs, lfqs), (&b, &f)| {
                let (new_bfqs, new_lfqs) = self.growth_tick_branch_return_fqs(b);

                (
                    mmerge(bfqs, mscale(new_bfqs, f)),
                    mmerge(lfqs, mscale(new_lfqs, f)),
                )
            },
        )
    }

    fn simulate_return_growth_time(&mut self) -> usize {
        for t in 1..1_000_000 {
            self.growth_tick();

            if self.leaf_num() >= self.limit {
                eprint!(".");
                return t;
            }
        }

        unreachable!()
    }

    fn leaf_num(&self) -> usize {
        self.leaf_fqs.values().sum()
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

    eprintln!("\n{result:?}");
    println!("{}", result.into_iter().sum::<usize>());
}
