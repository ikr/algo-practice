use ac_library::Dsu;
use proconio::input;
use proconio_derive::fastout;

fn can_make_it_with(xs: &[u32], h: u32) -> bool {
    let n = xs.len();
    let mut dsu = Dsu::new(n + 1);

    for (i, &x) in xs.iter().enumerate() {
        if x <= h {
            dsu.merge(n, i);
        }
    }

    for i in 1..n {
        let d = xs[i - 1].abs_diff(xs[i]);
        if d <= h {
            dsu.merge(i - 1, i);
        }
    }

    (0..n).all(|i| dsu.same(i, n))
}

fn shortest_ladder_height(xs: Vec<u32>) -> u32 {
    let mut lo: u32 = 0;
    assert!(!can_make_it_with(&xs, lo));
    let mut hi: u32 = 2 * xs.iter().max().unwrap();
    assert!(can_make_it_with(&xs, hi));

    while lo + 1 < hi {
        let mid = lo + (hi - lo) / 2;
        if can_make_it_with(&xs, mid) {
            hi = mid;
        } else {
            lo = mid;
        }
    }

    hi
}

#[fastout]
fn main() {
    input! {
        cases_num: u16,
    }

    for t in 1..=cases_num {
        input! {
            n: usize,
            xs: [u32; n],
        }

        let result = shortest_ladder_height(xs);
        println!("Case #{t}: {result}");
    }
}
