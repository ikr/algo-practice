use std::io::{self, BufRead};

#[derive(Clone, Copy, Debug)]
struct Crd(usize, usize);

impl Crd {
    fn parse(src: &str) -> Crd {
        let xs: Vec<usize> = src
            .split(',')
            .map(|s| s.parse::<usize>().unwrap())
            .collect();
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

    let mut grid: Vec<Vec<bool>> = vec![vec![false; 1000]; 1000];

    for Op {
        opcode,
        rct: Rct(Crd(a, b), Crd(c, d)),
    } in ops
    {
        for r in a..=c {
            for c in b..=d {
                match opcode {
                    Opcode::On => grid[r][c] = true,
                    Opcode::Off => grid[r][c] = false,
                    Opcode::Toggle => grid[r][c] = !grid[r][c],
                }
            }
        }
    }

    let result1 = grid.iter().fold(0, |acc, row| {
        acc + row.iter().fold(0, |sub, x| sub + if *x { 1 } else { 0 })
    });
    println!("{}", result1);
}
