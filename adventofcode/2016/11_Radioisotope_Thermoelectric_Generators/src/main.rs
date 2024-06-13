const N: usize = 2;

#[derive(Clone, Copy, Debug)]
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

    fn with_microchip(&self, x: u8) -> Floor {
        let mut result = *self;
        result.microchips[x as usize] = true;
        result
    }

    fn with_generator(&self, x: u8) -> Floor {
        let mut result = *self;
        result.generators[x as usize] = true;
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
}

#[derive(Clone, Copy, Debug)]
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
        assert!(!f.has_generators() || f.all_microchips_shielded());
    }
}
