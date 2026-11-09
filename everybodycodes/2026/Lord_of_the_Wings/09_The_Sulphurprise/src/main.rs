use itertools::Itertools;
use std::{
    collections::BTreeMap,
    io::{BufRead, stdin},
    ops::{Add, AddAssign, MulAssign},
};

type Freqs = BTreeMap<usize, usize>;

fn mmerge<K: Ord, V: AddAssign + Copy>(xs: BTreeMap<K, V>, ys: BTreeMap<K, V>) -> BTreeMap<K, V> {
    xs.into_iter().fold(ys, |mut agg, (i, x)| {
        agg.entry(i).and_modify(|y| *y += x).or_insert(x);
        agg
    })
}

fn mscale<K: Ord, V: MulAssign + Copy>(mut xs: BTreeMap<K, V>, factor: V) -> BTreeMap<K, V> {
    for x in xs.values_mut() {
        *x *= factor;
    }
    xs
}

fn mbump<K: Ord + Add<Output = K> + Copy, V: Copy>(
    xs: &BTreeMap<K, V>,
    delta: K,
) -> BTreeMap<K, V> {
    xs.iter().map(|(&k, &v)| (k + delta, v)).collect()
}

fn max_key<K: Copy + Default + Ord, V>(xs: &BTreeMap<K, V>) -> K {
    xs.last_key_value().map(|(k, _)| *k).unwrap_or_default()
}

#[derive(Debug)]
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

    fn leaf_num(&self) -> usize {
        self.leaf_fqs.values().sum()
    }

    fn idling_time(&self) -> usize {
        let hi = max_key(&self.leaf_fqs).max(max_key(&self.branch_fqs));
        assert!(hi < self.growth);
        self.growth - hi - 1
    }

    fn simulate_return_growth_time(&mut self) -> usize {
        let mut t = 1;

        if self.leaf_num() >= self.limit {
            eprint!(".");
            return t;
        }

        loop {
            let it = self.idling_time();

            if it == 0 {
                self.growth_tick();

                if self.leaf_num() >= self.limit {
                    eprint!(".");
                    return t;
                }

                t += 1;
            } else {
                self.branch_fqs = mbump(&self.branch_fqs, it);
                self.leaf_fqs = mbump(&self.leaf_fqs, it);
                t += it;
            }
        }
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
