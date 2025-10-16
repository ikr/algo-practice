use rand::Rng;

struct MaxCoinsComputation {
    xs: Vec<i32>,
    memo: Vec<Vec<Vec<i32>>>,
}

impl MaxCoinsComputation {
    fn new(xs: Vec<i32>) -> Self {
        let n = xs.len();
        let memo = vec![vec![vec![-1; n]; n]; n];
        Self { xs, memo }
    }

    fn recur(&mut self, lhs: usize, rhs: usize, last: usize) -> i32 {
        assert!(lhs < last && last < rhs);
        assert!(rhs - lhs >= 2);

        if self.memo[lhs][rhs][last] == -1 {
            self.memo[lhs][rhs][last] = {
                if lhs + 2 == rhs {
                    assert_eq!(last, lhs + 1);
                    self.xs[lhs] * self.xs[last] * self.xs[rhs]
                } else if lhs + 1 == last {
                    assert_ne!((last + 1..rhs).count(), 0);
                    let a = last;
                    let c = rhs;

                    (last + 1..rhs)
                        .map(|b| self.xs[lhs] * self.xs[last] * self.xs[rhs] + self.recur(a, c, b))
                        .max()
                        .unwrap()
                } else if last + 1 == rhs {
                    assert_ne!((lhs + 1..last).count(), 0);
                    let x = lhs;
                    let z = last;

                    (lhs + 1..last)
                        .map(|y| self.recur(x, z, y) + self.xs[lhs] * self.xs[last] * self.xs[rhs])
                        .max()
                        .unwrap()
                } else {
                    assert_ne!((last + 1..rhs).count(), 0);
                    assert_ne!((lhs + 1..last).count(), 0);
                    let x = lhs;
                    let z = last;
                    let a = last;
                    let c = rhs;

                    (last + 1..rhs)
                        .zip(lhs + 1..last)
                        .map(|(b, y)| {
                            self.recur(x, z, y)
                                + self.xs[lhs] * self.xs[last] * self.xs[rhs]
                                + self.recur(a, c, b)
                        })
                        .max()
                        .unwrap()
                }
            }
        }

        self.memo[lhs][rhs][last]
    }
}

impl Solution {
    pub fn max_coins(mut xs: Vec<i32>) -> i32 {
        xs.insert(0usize, 1i32);
        xs.push(1);

        let n = xs.len();
        let mut comp = MaxCoinsComputation::new(xs);
        (1..n - 1).map(|i| comp.recur(0, n - 1, i)).max().unwrap()
    }
}

struct Solution {}

fn random_sample(k: usize) -> Vec<i32> {
    let mut rng = rand::rng();
    (0..k).map(|_| rng.random_range(0..=100)).collect()
}

fn oracle(mut xs: Vec<i32>) -> i32 {
    xs.insert(0, 1);
    xs.push(1);
    let n = xs.len();

    let mut dp = vec![vec![0; n]; n];
    for i in (1..n - 1).rev() {
        for j in i..n - 1 {
            for k in i..=j {
                let coins = xs[i - 1] * xs[k] * xs[j + 1] + dp[i][k - 1] + dp[k + 1][j];
                dp[i][j] = dp[i][j].max(coins);
            }
        }
    }
    dp[1][n - 2]
}

fn main() {
    for _ in 0..10_000 {
        let xs = random_sample(4);
        let actual = Solution::max_coins(xs.clone());
        let expected = oracle(xs.clone());
        assert_eq!(
            actual, expected,
            "Got {actual}, expected {expected}, failed on {:?}",
            xs
        );
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_solution() {
        for (xs, res) in [
            (vec![3, 1, 5, 8], 167),
            (vec![1, 5], 10),
            (vec![4, 21, 3, 100, 0, 99], 223011),
            (vec![0, 78, 95, 27], 202254),
            (
                vec![
                    57, 12, 84, 6, 39, 93, 28, 47, 65, 78, 21, 90, 4, 54, 11, 99, 36, 73, 15, 32,
                ],
                5608314,
            ),
        ] {
            assert_eq!(Solution::max_coins(xs.clone()), res, "Failed on {:?}", xs);
        }
    }
}
