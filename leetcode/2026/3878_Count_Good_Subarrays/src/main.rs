// Source:
// https://github.com/kenkoooo/competitive-programming-rs/blob/master/src/data_structure/segment_tree.rs
//
pub struct SegmentTree<T, Op> {
    seg: Vec<Option<T>>,
    n: usize,
    op: Op,
}

impl<T, Op> SegmentTree<T, Op>
where
    T: Copy,
    Op: Fn(T, T) -> T + Copy,
{
    pub fn new(size: usize, op: Op) -> SegmentTree<T, Op> {
        let mut m = size.next_power_of_two();
        if m == size {
            m *= 2;
        }
        SegmentTree {
            seg: vec![None; m * 2],
            n: m,
            op,
        }
    }

    pub fn update(&mut self, k: usize, value: T) {
        let mut k = k;
        k += self.n - 1;
        self.seg[k] = Some(value);
        while k > 0 {
            k = (k - 1) >> 1;
            let left = self.seg[k * 2 + 1];
            let right = self.seg[k * 2 + 2];
            self.seg[k] = Self::op(left, right, self.op);
        }
    }

    /// Get the result in the array of the range
    pub fn query<R: std::ops::RangeBounds<usize>>(&self, range: R) -> Option<T> {
        let start = match range.start_bound() {
            std::ops::Bound::Included(t) => *t,
            std::ops::Bound::Excluded(t) => *t + 1,
            std::ops::Bound::Unbounded => 0,
        };

        let end = match range.end_bound() {
            std::ops::Bound::Included(t) => *t + 1,
            std::ops::Bound::Excluded(t) => *t,
            std::ops::Bound::Unbounded => self.n,
        };

        self.query_range(start..end, 0, 0..self.n)
    }

    fn query_range(
        &self,
        range: std::ops::Range<usize>,
        k: usize,
        seg_range: std::ops::Range<usize>,
    ) -> Option<T> {
        if seg_range.end <= range.start || range.end <= seg_range.start {
            None
        } else if range.start <= seg_range.start && seg_range.end <= range.end {
            self.seg[k]
        } else {
            let mid = (seg_range.start + seg_range.end) >> 1;
            let x = self.query_range(range.clone(), k * 2 + 1, seg_range.start..mid);
            let y = self.query_range(range, k * 2 + 2, mid..seg_range.end);
            Self::op(x, y, self.op)
        }
    }

    fn op(a: Option<T>, b: Option<T>, f: Op) -> Option<T> {
        match (a, b) {
            (Some(a), Some(b)) => Some(f(a, b)),
            _ => a.or(b),
        }
    }
}

pub struct SegmentTree2d<T, Op> {
    n: usize,
    seg: Vec<SegmentTree<T, Op>>,
    op: Op,
}

impl<T, Op> SegmentTree2d<T, Op>
where
    T: Copy,
    Op: Fn(T, T) -> T + Copy,
{
    pub fn new(h: usize, w: usize, op: Op) -> Self {
        let mut n = h.next_power_of_two();
        if n == h {
            n *= 2;
        }
        let mut seg = Vec::with_capacity(n * 2);
        for _ in 0..(n * 2) {
            seg.push(SegmentTree::new(w, op));
        }
        Self { seg, n, op }
    }

    pub fn update(&mut self, i: usize, j: usize, value: T) {
        let mut k = i;
        k += self.n - 1;
        self.seg[k].update(j, value);
        while k > 0 {
            k = (k - 1) >> 1;
            let left = self.seg[k * 2 + 1].query(j..(j + 1));
            let right = self.seg[k * 2 + 2].query(j..(j + 1));
            if let Some(value) = Self::op(left, right, self.op) {
                self.seg[k].update(j, value);
            }
        }
    }

    pub fn query<C, R>(&self, r: R, c: C) -> Option<T>
    where
        C: std::ops::RangeBounds<usize>,
        R: std::ops::RangeBounds<usize>,
    {
        let start = |s: std::ops::Bound<&usize>| match s {
            std::ops::Bound::Included(t) => *t,
            std::ops::Bound::Excluded(t) => *t + 1,
            std::ops::Bound::Unbounded => 0,
        };

        let end = |e: std::ops::Bound<&usize>| match e {
            std::ops::Bound::Included(t) => *t + 1,
            std::ops::Bound::Excluded(t) => *t,
            std::ops::Bound::Unbounded => self.n,
        };

        let r_start = start(r.start_bound());
        let c_start = start(c.start_bound());
        let r_end = end(r.end_bound());
        let c_end = end(c.end_bound());

        self.query_range(r_start..r_end, 0, 0..self.n, c_start..c_end)
    }

    fn query_range(
        &self,
        range: std::ops::Range<usize>,
        k: usize,
        seg_range: std::ops::Range<usize>,
        c: std::ops::Range<usize>,
    ) -> Option<T> {
        if seg_range.end <= range.start || range.end <= seg_range.start {
            None
        } else if range.start <= seg_range.start && seg_range.end <= range.end {
            self.seg[k].query(c)
        } else {
            let mid = (seg_range.start + seg_range.end) >> 1;
            let x = self.query_range(range.clone(), k * 2 + 1, seg_range.start..mid, c.clone());
            let y = self.query_range(range, k * 2 + 2, mid..seg_range.end, c);
            Self::op(x, y, self.op)
        }
    }
    fn op(a: Option<T>, b: Option<T>, f: Op) -> Option<T> {
        match (a, b) {
            (Some(a), Some(b)) => Some(f(a, b)),
            _ => a.or(b),
        }
    }
}

fn count_good_subarrays_impl(xs: Vec<i32>) -> usize {
    let n = xs.len();
    let ii: Vec<usize> = (0..n).collect();
    let mut seg = SegmentTree::new(n, |a: i32, b: i32| a | b);

    for (i, &x) in xs.iter().enumerate() {
        seg.update(i, x);
    }

    xs.into_iter()
        .enumerate()
        .map(|(i0, x0)| -> usize {
            let l = ii[0..=i0].partition_point(|&i| seg.query(i..=i0).unwrap() != x0);
            let r = ii[i0..n].partition_point(|&i| seg.query(i0..=i).unwrap() == x0);
            let sub = (i0 - l + 1) * r;
            println!("i0:{i0} l:{l} r:{r} sub:{sub}");
            sub
        })
        .sum()
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

fn main() {
    println!("Does nothing; please run the tests.");
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn problem_statement_example_1() {
        assert_eq!(Solution::count_good_subarrays(vec![4, 2, 3]), 4);
    }

    #[test]
    fn problem_statement_example_2() {
        assert_eq!(Solution::count_good_subarrays(vec![1, 3, 1]), 6);
    }

    #[test]
    fn other_test_cases() {
        for (arg, res) in vec![(vec![6, 6], 3)] {
            assert_eq!(Solution::count_good_subarrays(arg), res);
        }
    }
}
