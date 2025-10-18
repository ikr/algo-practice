use ac_library::ModInt1000000007 as Mint;
use primal::Sieve;
use proconio::input;
use proconio_derive::fastout;

fn sequences_num(sieve: &Sieve, n: usize, a: usize, b: usize) -> Mint {
    todo!()
}

#[fastout]
fn main() {
    let sieve = primal::Sieve::new(10_000_000);

    input! {
        cases_num: u16,
    }

    for t in 1..=cases_num {
        input! {
            n: usize,
            a: usize,
            b: usize,
        }

        let result: u32 = sequences_num(&sieve, n, a, b).val();
        println!("Case #{t}: {result}");
    }
}
