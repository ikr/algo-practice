use std::io::stdin;

use itertools::Itertools;

/// NEW PLAN (no code changes towards it just yet!)
///
/// Suppose xs has n elements. Let's move the "current" index i from 0 to `n - 1`. We'll count all
/// the good sub-arrays ending exactly at i. For that, while scanning through xs (with `i`), we'll
/// maintain two pieces of state:
///
/// A) The "current" array of pairs (L1, V1), (L2, V2), ... where Lj is the leftmost index such that
/// a bitwise OR of xs' values within indices interval [a, i] equals Vj, for any `a` within [Lj,
/// L{j+1} - 1]. Here, if a < b, then La < Lb, and also (Va & Vb) == Vb -- only new bits can appear
/// as we keep OR-ing from index i to the left. All the Vj-s are distinct.
///
/// B) For every value x from xs, what's its largest index so far? We'll name that index Rx.
///
/// An important property of the (Lj, Vj) pairs array is that its size is limited (for every i) by
/// the number of bits each of the xs values has, which is 32.
///
/// Then, having the (Lj, Vj) array, and the x -> Rx map, we can compute the number of good
/// sub-arrays ending exactly at index i. It's the sum of Mj values over all j such that Vj is
/// present as a key in the x -> Rx map, and Lj <= R{Vj}; Mj = min(L{j+1}, R{Vj}) - Lj.
///
fn count_good_subarrays_impl(xs: Vec<i32>) -> usize {
    todo!()
}

impl Solution {
    pub fn count_good_subarrays(xs: Vec<i32>) -> i64 {
        count_good_subarrays_impl(xs) as i64
    }
}

// You are given an integer array xs.
//
// An array is called good if the bitwise OR over all of its elements is equal
// to at least one element present in that array.
//
// Return the number of good sub-arrays in xs.
struct Solution {}

fn count_good_subarrays_brute_force(xs: Vec<i32>) -> usize {
    fn bitwise_or(ys: &[i32]) -> i32 {
        ys.iter().fold(0, |acc, &y| acc | y)
    }

    (0..xs.len())
        .combinations_with_replacement(2)
        .filter(|ij| {
            let (i, j) = (ij[0], ij[1]);
            let o = bitwise_or(&xs[i..=j]);
            xs[i..=j].contains(&o)
        })
        .count()
}

fn main() {
    let mut line = String::new();
    stdin().read_line(&mut line).unwrap();

    let xs: Vec<i32> = line
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    let result = Solution::count_good_subarrays(xs.clone());
    assert_eq!(count_good_subarrays_brute_force(xs), result as usize);
    println!("{result}");
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn solution_for_problem_statement_example_1() {
        assert_eq!(Solution::count_good_subarrays(vec![4, 2, 3]), 4);
    }

    #[test]
    fn solution_for_problem_statement_example_2() {
        assert_eq!(Solution::count_good_subarrays(vec![1, 3, 1]), 6);
    }

    #[test]
    #[ignore = "not ready yet"]
    fn solution_for_other_test_cases() {
        for (arg, res) in vec![(vec![6, 6], 3)] {
            assert_eq!(Solution::count_good_subarrays(arg), res);
        }
    }

    #[test]
    fn test_count_good_subarrays_brute_force() {
        for (arg, res) in vec![(vec![4, 2, 3], 4), (vec![1, 3, 1], 6), (vec![6, 6], 3)] {
            assert_eq!(count_good_subarrays_brute_force(arg), res);
        }
    }
}
