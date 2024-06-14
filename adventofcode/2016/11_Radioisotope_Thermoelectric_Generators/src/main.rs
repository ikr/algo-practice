const N: usize = 2;

fn intersect<const K: usize>(a: [bool; K], b: [bool; K]) -> bool {
    a.into_iter().enumerate().any(|(i, x)| x && x == b[i])
}

#[derive(Clone, Copy, Debug, Hash)]
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

#[derive(Clone, Copy, Debug, Hash)]
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
}

fn in_a() -> Vertex {
    Vertex::new([
        Floor::new().with_microchip(0).with_microchip(1),
        Floor::new().with_generator(0),
        Floor::new().with_generator(1),
        Floor::new(),
    ])
}

fn main() {
    let u = in_a();
    eprintln!("{:?}", u);
    for f in u.floors {
        assert!(f.is_safe());
    }

    eprintln!("{:?}", u.floors[0].all_moves(u.floors[1]));
}
