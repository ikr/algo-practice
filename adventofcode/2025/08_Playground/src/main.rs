use ac_library::Dsu;
use itertools::Itertools;
use std::io::{BufRead, stdin};

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i64, i64, i64);

impl Crd {
    fn components(self) -> Vec<i64> {
        vec![self.0, self.1, self.2]
    }

    fn dist2(self, o: Crd) -> i64 {
        (o - self).components().into_iter().map(|a| a * a).sum()
    }

    fn decode(s: &str) -> Self {
        let (a, b, c) = s
            .split(',')
            .map(|ss| ss.parse::<i64>().unwrap())
            .collect_tuple()
            .unwrap();

        Self(a, b, c)
    }
}

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1, self.2 + o.2)
    }
}

impl std::ops::Sub<Crd> for Crd {
    type Output = Crd;

    fn sub(self, o: Crd) -> Crd {
        Crd(self.0 - o.0, self.1 - o.1, self.2 - o.2)
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let crds: Vec<Crd> = lines.into_iter().map(|line| Crd::decode(&line)).collect();
    let n = crds.len();

    let pairs: Vec<(usize, usize)> = (0..n)
        .tuple_combinations()
        .sorted_by_key(|&(i, j)| crds[i].dist2(crds[j]))
        .collect();

    let mut dsu = Dsu::new(n);
    for (i, j) in pairs {
        dsu.merge(i, j);
        if dsu.size(i) == n {
            let result = crds[i].0 * crds[j].0;
            println!("{result}");
            break;
        }
    }
}
