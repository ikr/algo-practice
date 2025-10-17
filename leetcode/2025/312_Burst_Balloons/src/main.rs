struct MaxCoinsComputation {
    xs: Vec<i32>,
    memo: Vec<Vec<i32>>,
}

impl MaxCoinsComputation {
    fn new(xs: Vec<i32>) -> Self {
        let n = xs.len();
        let memo = vec![vec![-1; n]; n];
        Self { xs, memo }
    }

    fn recur(&mut self, i: usize, j: usize) -> i32 {
        if self.memo[i][j] == -1 {
            self.memo[i][j] = if j < i {
                0
            } else {
                (i..=j)
                    .map(|h| {
                        self.recur(i, h - 1)
                            + self.xs[i - 1] * self.xs[h] * self.xs[j + 1]
                            + self.recur(h + 1, j)
                    })
                    .max()
                    .unwrap()
            }
        }

        self.memo[i][j]
    }
}

impl Solution {
    #[allow(dead_code)]
    pub fn max_coins(mut xs: Vec<i32>) -> i32 {
        xs.insert(0usize, 1i32);
        xs.push(1);

        let n = xs.len();
        let mut comp = MaxCoinsComputation::new(xs);
        comp.recur(1, n - 2)
    }
}

struct Solution {}

fn main() {
    unreachable!()
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
            (vec![0, 4, 0, 1], 8),
            (vec![6, 3, 4, 6, 4, 10, 6], 1218),
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
