use ac_library::StaticModInt;
use std::io::{BufRead, stdin};

macro_rules! modulus {
    ($($name:ident($value:expr, $is_prime:expr)),*) => {
        $(
            #[derive(Copy, Clone, Eq, PartialEq)]
            enum $name {}

            impl ac_library::modint::Modulus for $name {
                const VALUE: u32 = $value;
                const HINT_VALUE_IS_PRIME: bool = $is_prime;

                fn butterfly_cache() -> &'static ::std::thread::LocalKey<::std::cell::RefCell<::std::option::Option<ac_library::modint::ButterflyCache<Self>>>> {
                    thread_local! {
                        static BUTTERFLY_CACHE: ::std::cell::RefCell<::std::option::Option<ac_library::modint::ButterflyCache<$name>>> = ::std::default::Default::default();
                    }
                    &BUTTERFLY_CACHE
                }
            }
        )*
    };
}

modulus!(Mod1073741824(1073741824, false));
type Mint = StaticModInt<Mod1073741824>;

#[derive(Clone, Copy, Debug, PartialEq)]
enum ShiftSubj {
    Row(usize),
    Col(usize),
}

#[derive(Clone, Copy, Debug, PartialEq)]
enum ArithmeticSubj {
    Row(usize),
    Col(usize),
    All,
}

#[derive(Clone, Copy, Debug, PartialEq)]
enum ArithmeticOp {
    Add(u32),
    Sub(u32),
    Mul(u32),
}

impl ArithmeticOp {
    fn decode(opcode: &str, arg: &str) -> Self {
        let x: u32 = arg.parse().unwrap();

        match opcode {
            "ADD" => Self::Add(x),
            "SUB" => Self::Sub(x),
            "MULTIPLY" => Self::Mul(x),
            _ => panic!("Unknown arithmetic opcode `{}`", opcode),
        }
    }

    fn apply(self, arg: Mint) -> Mint {
        match self {
            Self::Add(x) => arg + x,
            Self::Sub(x) => arg - x,
            Self::Mul(x) => arg * x,
        }
    }
}

#[derive(Clone, Copy, Debug, PartialEq)]
enum Instr {
    ShiftInstr(ShiftSubj, u32),
    ArithmeticInstr(ArithmeticSubj, ArithmeticOp),
}

impl Instr {
    fn decode(s: &str) -> Self {
        let ps: Vec<_> = s.split_whitespace().collect();
        if ps[0] == "SHIFT" {
            match ps[1] {
                "ROW" => Instr::ShiftInstr(
                    ShiftSubj::Row(ps[2].parse().unwrap()),
                    ps[4].parse().unwrap(),
                ),
                "COL" => Instr::ShiftInstr(
                    ShiftSubj::Col(ps[2].parse().unwrap()),
                    ps[4].parse().unwrap(),
                ),
                _ => panic!("Unknown shift subject `{}`", ps[1]),
            }
        } else {
            let subj: ArithmeticSubj = if ps[2] == "ALL" {
                ArithmeticSubj::All
            } else {
                match ps[2] {
                    "ROW" => ArithmeticSubj::Row(ps[3].parse().unwrap()),
                    "COL" => ArithmeticSubj::Col(ps[3].parse().unwrap()),
                    _ => panic!("Unknown arithmetic subject `{}`", ps[2]),
                }
            };
            let op = ArithmeticOp::decode(ps[0], ps[1]);
            Instr::ArithmeticInstr(subj, op)
        }
    }
}

#[derive(Clone, Debug)]
struct Grid {
    rows: Vec<Vec<Mint>>,
}

impl Grid {
    fn transpose(&self) -> Grid {
        assert!(!self.rows.is_empty());
        let h = self.rows[0].len();
        let mut iters: Vec<_> = self.rows.iter().cloned().map(|n| n.into_iter()).collect();
        let rows = (0..h)
            .map(|_| {
                iters
                    .iter_mut()
                    .map(|n| n.next().unwrap())
                    .collect::<Vec<_>>()
            })
            .collect();
        Grid { rows }
    }

    fn arithmetic_on_row(&self, i: usize, op: ArithmeticOp) -> Grid {
        let mut rows = self.rows.clone();
        for cell in rows[i].iter_mut() {
            *cell = op.apply(*cell);
        }
        Grid { rows }
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let i_sep_a: usize = lines.iter().position(|s| s.is_empty()).unwrap();
    let i_sep_b: usize = lines.iter().rposition(|s| s.is_empty()).unwrap();

    let rows: Vec<Vec<Mint>> = lines[..i_sep_a]
        .iter()
        .map(|s| {
            s.split_whitespace()
                .map(|ss| Mint::new(ss.parse::<u32>().unwrap()))
                .collect::<Vec<_>>()
        })
        .collect();
    eprintln!("{:?}", rows);

    let ops: Vec<Instr> = lines[i_sep_a + 1..i_sep_b]
        .iter()
        .map(|s| Instr::decode(s))
        .collect();
    eprintln!("{:?}", ops);
}
