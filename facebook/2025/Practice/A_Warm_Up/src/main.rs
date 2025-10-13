use std::collections::HashMap;

use proconio::input;
use proconio_derive::fastout;

fn swapped_pairs(aa: Vec<u32>, bb: Vec<u32>) -> Option<Vec<(usize, usize)>> {
    let n = aa.len();
    let mut ii: Vec<usize> = (0..n).collect();
    ii.sort_by_key(|&i| bb[i]);

    let idx: HashMap<u32, usize> = aa.iter().enumerate().map(|(i, &a)| (a, i)).collect();
    let mut result: Vec<(usize, usize)> = vec![];

    for i in ii {
        if aa[i] > bb[i] {
            return None;
        }

        if aa[i] == bb[i] {
            continue;
        }

        if let Some(&j) = idx.get(&bb[i]) {
            result.push((i, j));
        } else {
            return None;
        }
    }

    Some(result)
}

#[fastout]
fn main() {
    input! {
        cases_num: u16,
    }

    for t in 1..=cases_num {
        input! {
            n: usize,
            aa: [u32; n],
            bb: [u32; n],
        }

        let result = swapped_pairs(aa, bb);
        if let Some(ii) = result {
            println!("Case #{t}: {}", ii.len());
            for (i, j) in ii {
                println!("{} {}", i + 1, j + 1);
            }
        } else {
            println!("Case #{t}: -1");
        }
    }
}
