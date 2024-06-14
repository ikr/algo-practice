use std::{
    collections::{HashSet, VecDeque},
    process::exit,
};

const N: usize = 5;

fn intersect<const K: usize>(a: [bool; K], b: [bool; K]) -> bool {
    a.into_iter().enumerate().any(|(i, x)| x && x == b[i])
}

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Floor {
    microchips: [bool; N],
    generators: [bool; N],
}

impl Floor {
    fn new() -> Floor {
        Floor {
            microchips: [false; N],
            generators: [false; N],
        }
    }

    fn with_microchip(&self, x: usize) -> Floor {
        let mut result = *self;
        result.microchips[x] = true;
        result
    }

    fn with_generator(&self, x: usize) -> Floor {
        let mut result = *self;
        result.generators[x] = true;
        result
    }

    fn without_microchip(&self, x: usize) -> Floor {
        let mut result = *self;
        result.microchips[x] = false;
        result
    }

    fn without_generator(&self, x: usize) -> Floor {
        let mut result = *self;
        result.generators[x] = false;
        result
    }

    fn has_generators(&self) -> bool {
        self.generators.iter().any(|x| *x)
    }

    fn all_microchips_shielded(&self) -> bool {
        self.microchips
            .iter()
            .enumerate()
            .filter(|(_, m)| **m)
            .fold(true, |acc, (i, m)| acc && *m && self.generators[i])
    }

    fn is_safe(&self) -> bool {
        !self.has_generators() || self.all_microchips_shielded()
    }

    fn is_full(&self) -> bool {
        self.microchips.iter().filter(|x| **x).count() == N
            && self.generators.iter().filter(|x| **x).count() == N
    }

    fn intersects(&self, oth: Floor) -> bool {
        intersect(self.microchips, oth.microchips) || intersect(self.generators, oth.generators)
    }

    fn couple_moves(&self, dst: Floor) -> Vec<(Floor, Floor)> {
        assert!(self.is_safe());
        assert!(dst.is_safe());
        assert!(!self.intersects(dst));
        let mut result = Vec::new();

        for (i, m) in self.microchips.iter().enumerate() {
            if *m && self.generators[i] {
                let dst_prime = dst.with_microchip(i).with_generator(i);
                if dst_prime.is_safe() {
                    result.push((self.without_microchip(i).without_generator(i), dst_prime));
                }
            }
        }

        result
    }

    fn one_microchip_moves(&self, dst: Floor) -> Vec<(Floor, Floor)> {
        assert!(self.is_safe());
        assert!(dst.is_safe());
        assert!(!self.intersects(dst));
        let mut result = Vec::new();

        for (i, m) in self.microchips.iter().enumerate() {
            if *m {
                let dst_prime = dst.with_microchip(i);
                if dst_prime.is_safe() {
                    result.push((self.without_microchip(i), dst_prime));
                }
            }
        }

        result
    }

    fn two_microchips_moves(&self, dst: Floor) -> Vec<(Floor, Floor)> {
        assert!(self.is_safe());
        assert!(dst.is_safe());
        assert!(!self.intersects(dst));
        let mut result = Vec::new();

        for i in 0..N - 1 {
            for j in i + 1..N {
                if self.microchips[i] && self.microchips[j] {
                    let dst_prime = dst.with_microchip(i).with_microchip(j);
                    if dst_prime.is_safe() {
                        result.push((self.without_microchip(i).without_microchip(j), dst_prime));
                    }
                }
            }
        }

        result
    }

    fn one_generator_moves(&self, dst: Floor) -> Vec<(Floor, Floor)> {
        assert!(self.is_safe());
        assert!(dst.is_safe());
        assert!(!self.intersects(dst));
        let mut result = Vec::new();

        for (i, g) in self.generators.iter().enumerate() {
            if *g {
                let src_prime = self.without_generator(i);
                if src_prime.is_safe() {
                    let dst_prime = dst.with_generator(i);
                    if dst_prime.is_safe() {
                        result.push((self.without_generator(i), dst_prime));
                    }
                }
            }
        }

        result
    }

    fn two_generators_moves(&self, dst: Floor) -> Vec<(Floor, Floor)> {
        assert!(self.is_safe());
        assert!(dst.is_safe());
        assert!(!self.intersects(dst));
        let mut result = Vec::new();

        for i in 0..N - 1 {
            for j in i + 1..N {
                if self.generators[i] && self.generators[j] {
                    let src_prime = self.without_generator(i).without_generator(j);
                    if src_prime.is_safe() {
                        let dst_prime = dst.with_generator(i).with_generator(j);
                        if dst_prime.is_safe() {
                            result
                                .push((self.without_generator(i).without_generator(j), dst_prime));
                        }
                    }
                }
            }
        }

        result
    }

    fn all_moves(&self, dst: Floor) -> Vec<(Floor, Floor)> {
        [
            self.couple_moves(dst),
            self.one_microchip_moves(dst),
            self.two_microchips_moves(dst),
            self.one_generator_moves(dst),
            self.two_generators_moves(dst),
        ]
        .concat()
    }
}

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Vertex {
    current_floor: u8,
    floors: [Floor; 4],
}

impl Vertex {
    fn new(floors: [Floor; 4]) -> Vertex {
        Vertex {
            current_floor: 0,
            floors,
        }
    }

    fn is_terminal(&self) -> bool {
        if self.floors[3].is_full() {
            assert!(self.current_floor == 3);
        }
        self.floors[3].is_full()
    }

    fn adjacent(&self) -> Vec<Vertex> {
        let c = self.current_floor as usize;
        let ijs: Vec<(usize, usize)> = match self.current_floor {
            0 => vec![(0, 1)],
            1 | 2 => vec![(c, c - 1), (c, c + 1)],
            3 => vec![(3, 2)],
            _ => panic!("Invalid current floor {}", self.current_floor),
        };

        let mut result: Vec<Vertex> = vec![];
        for (i, j) in ijs {
            for (f0, f1) in self.floors[i].all_moves(self.floors[j]) {
                let mut v: Vertex = *self;
                v.floors[i] = f0;
                v.floors[j] = f1;
                v.current_floor = j as u8;
                result.push(v);
            }
        }
        result
    }
}

// fn in_a() -> Vertex {
//     Vertex::new([
//         Floor::new().with_microchip(0).with_microchip(1),
//         Floor::new().with_generator(0),
//         Floor::new().with_generator(1),
//         Floor::new(),
//     ])
// }

// promethium: 0
//     cobalt: 1
//     curium: 2
//  ruthenium: 3
//  plutonium: 4
fn in_1() -> Vertex {
    Vertex::new([
        Floor::new().with_generator(0).with_microchip(0),
        Floor::new()
            .with_generator(1)
            .with_generator(2)
            .with_generator(3)
            .with_generator(4),
        Floor::new()
            .with_microchip(1)
            .with_microchip(2)
            .with_microchip(3)
            .with_microchip(4),
        Floor::new(),
    ])
}

fn main() {
    let u0 = in_1();
    let mut discovered: HashSet<Vertex> = HashSet::from([u0]);
    let mut q: VecDeque<(Vertex, u32)> = VecDeque::new();
    q.push_back((u0, 0));

    while let Some((u, d)) = q.pop_front() {
        for v in u.adjacent() {
            if !discovered.contains(&v) {
                if v.is_terminal() {
                    println!("{}", d + 1);
                    exit(0);
                }
                q.push_back((v, d + 1));
                discovered.insert(v);
            }
        }
    }
}
