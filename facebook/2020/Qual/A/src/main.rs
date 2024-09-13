use proconio::input;
use proconio::marker::Bytes;
use proconio_derive::fastout;

fn solve(ins: &[u8], outs: &[u8]) -> Vec<Vec<u8>> {
    let n = ins.len();
    vec![vec![b'Y'; n]; n]
}

#[fastout]
fn main() {
    input! {
        cases_num: u16,
    }

    for t in 1..=cases_num {
        input! {
            n: usize,
            ins: Bytes,
            outs: Bytes,
        }

        assert_eq!(ins.len(), n);
        assert_eq!(outs.len(), n);

        println!("Case #{}", t);
        for row in solve(&ins, &outs) {
            println!("{}", std::str::from_utf8(&row).unwrap());
        }
    }
}
