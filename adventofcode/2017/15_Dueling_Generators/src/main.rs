const FA: u64 = 16807;
const FB: u64 = 48271;
const M: u64 = 2147483647;

struct Generator {
    factor: u64,
    multiples_of: u64,
    value: u64,
}

impl Generator {
    fn tick(&mut self) {
        loop {
            self.value *= self.factor;
            self.value %= M;
            if self.value % self.multiples_of == 0 {
                break;
            }
        }
    }

    fn digest(&self) -> u16 {
        (self.value & ((1u64 << 16) - 1)) as u16
    }
}

fn read_suffix_number() -> u64 {
    let mut line = String::new();
    std::io::stdin().read_line(&mut line).unwrap();
    line.split_whitespace().last().unwrap().parse().unwrap()
}

fn main() {
    let a0 = read_suffix_number();
    let b0 = read_suffix_number();

    let mut ga = Generator {
        factor: FA,
        multiples_of: 4,
        value: a0,
    };

    let mut gb = Generator {
        factor: FB,
        multiples_of: 8,
        value: b0,
    };

    let mut result = 0;
    for _ in 0..5_000_000 {
        ga.tick();
        gb.tick();
        if ga.digest() == gb.digest() {
            result += 1;
        }
    }
    println!("{}", result);
}
