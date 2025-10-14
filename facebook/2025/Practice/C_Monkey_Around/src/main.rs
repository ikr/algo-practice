use proconio::input;
use proconio_derive::fastout;

#[derive(Clone, Copy)]
enum Op {
    Append(usize),
    Rotate,
}

impl Op {
    fn represent(self) -> String {
        match self {
            Self::Append(k) => format!("1 {k}"),
            Self::Rotate => 2.to_string(),
        }
    }
}

fn deconstruct_program(xs: Vec<usize>) -> Vec<Op> {
    vec![Op::Append(3), Op::Rotate]
}

#[fastout]
fn main() {
    input! {
        cases_num: u16,
    }

    for t in 1..=cases_num {
        input! {
            n: usize,
            xs: [usize; n],
        }

        let result = deconstruct_program(xs);
        assert!(result.len() <= 2 * n);
        println!("Case #{t}: {}", result.len());

        for op in result {
            println!("{}", op.represent());
        }
    }
}
