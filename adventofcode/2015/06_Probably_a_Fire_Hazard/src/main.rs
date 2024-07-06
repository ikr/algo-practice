use std::io::{self, BufRead};

#[derive(Clone, Copy, Debug)]
struct Crd(i32, i32);

impl Crd {
    fn parse(src: &str) -> Crd {
        let xs: Vec<i32> = src.split(',').map(|s| s.parse::<i32>().unwrap()).collect();
        let [r, c] = xs[..] else {
            panic!("{:?} isn't a pair", xs)
        };
        Crd(r, c)
    }
}

#[derive(Clone, Copy, Debug)]
struct Rct(Crd, Crd);

impl Rct {
    fn parse(src: &str) -> Rct {
        let subs: Vec<Crd> = src.split(" through ").map(Crd::parse).collect();
        let [a, b] = subs[..] else {
            panic!("{:?} isn't a pair", subs)
        };
        assert!(a.0 <= b.0);
        assert!(a.1 <= b.1);
        Rct(a, b)
    }
}

#[derive(Clone, Copy, Debug)]
enum Opcode {
    On,
    Off,
    Toggle,
}

#[derive(Clone, Copy, Debug)]
struct Op {
    opcode: Opcode,
    rct: Rct,
}

impl Op {
    fn parse(src: &str) -> Op {
        for (prefix, opcode) in [
            ("turn on ", Opcode::On),
            ("turn off ", Opcode::Off),
            ("toggle ", Opcode::Toggle),
        ] {
            if let Some(suffix) = src.strip_prefix(prefix) {
                let rct = Rct::parse(suffix);
                return Op { opcode, rct };
            }
        }
        panic!("{} starts with an invalid operation prefix", src);
    }
}

fn main() {
    let ops: Vec<Op> = io::stdin()
        .lock()
        .lines()
        .map(|line| Op::parse(&line.unwrap()))
        .collect();
    eprintln!("{:?}", ops);
}
