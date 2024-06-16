use std::collections::{HashSet, VecDeque};

const SEED: i32 = 1350;

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i32, i32);

impl Crd {
    fn is_wall(&self) -> bool {
        let x = self.0;
        let y = self.1;
        if x < 0 || y < 0 {
            false
        } else {
            let v = x * x + 3 * x + 2 * x * y + y + y * y + SEED;
            v.count_ones() % 2 == 1
        }
    }

    fn adjacent(&self) -> Vec<Crd> {
        Dir::all()
            .into_iter()
            .map(|d| *self + d.delta())
            .filter(|crd| !crd.is_wall())
            .collect()
    }
}

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

#[derive(Clone, Copy, Debug)]
enum Dir {
    N,
    E,
    S,
    W,
}

impl Dir {
    fn all() -> [Dir; 4] {
        [Dir::N, Dir::E, Dir::S, Dir::W]
    }

    fn delta(&self) -> Crd {
        match self {
            Dir::N => Crd(-1, 0),
            Dir::E => Crd(0, 1),
            Dir::S => Crd(1, 0),
            Dir::W => Crd(0, -1),
        }
    }
}

fn main() {
    let src = Crd(1, 1);

    let mut visited: HashSet<Crd> = HashSet::from([src]);
    let mut q: VecDeque<(Crd, i32)> = VecDeque::from([(src, 0)]);

    while let Some((u, s)) = q.pop_front() {
        for v in u.adjacent() {
            if !visited.contains(&v) && s < 50 {
                visited.insert(v);
                q.push_back((v, s + 1));
            }
        }
    }

    println!("{}", visited.len());
}
