use itertools::Itertools;
use proconio::{
    input_interactive,
    marker::{Isize1, Usize1},
};
use std::collections::{HashSet, VecDeque};

fn partitions(tree: &[Vec<usize>]) -> (Vec<usize>, Vec<usize>) {
    let n = tree.len();
    let mut label: Vec<Option<bool>> = vec![None; n];

    for u0 in 0..n {
        if label[u0].is_none() {
            let mut q: VecDeque<usize> = VecDeque::from([u0]);
            label[u0] = Some(true);

            while let Some(u) = q.pop_front() {
                let own_l = label[u].unwrap();
                for &v in tree[u].iter() {
                    if let Some(l) = label[v] {
                        assert_ne!(own_l, l);
                    } else {
                        label[v] = Some(!own_l);
                    }
                }
            }
        }
    }

    label
        .into_iter()
        .enumerate()
        .fold((vec![], vec![]), |(mut yepp, mut nope), (u, l)| {
            if l.unwrap() {
                yepp.push(u);
            } else {
                nope.push(u);
            }
            (yepp, nope)
        })
}

fn canonical(uv: (usize, usize)) -> (usize, usize) {
    let (u, v) = uv;
    assert_ne!(u, v);
    (u.min(v), u.max(v))
}

fn main() {
    input_interactive! {
        n: usize,
        xs: [(Usize1, Usize1); n - 1],
    }

    let g: Vec<Vec<usize>> = xs.iter().fold(vec![vec![]; n], |mut g, &(u, v)| {
        g[u].push(v);
        g[v].push(u);
        g
    });

    let initial_edges: HashSet<(usize, usize)> = xs.into_iter().map(canonical).collect();

    let (a, b) = partitions(&g);

    let mut non_edges: HashSet<(usize, usize)> = a
        .into_iter()
        .cartesian_product(b)
        .map(canonical)
        .filter(|uv| !initial_edges.contains(uv))
        .collect();

    if non_edges.len() % 2 == 0 {
        println!("Second");
    } else {
        println!("First");
        let uv: (usize, usize) = *non_edges.iter().next().unwrap();
        non_edges.remove(&uv);
        println!("{} {}", uv.0, uv.1);
    }

    loop {
        input_interactive! {
            i: Isize1,
            j: Isize1,
        }

        if i == -2 {
            return;
        }

        non_edges.remove(&canonical((i as usize, j as usize)));
        let uv: (usize, usize) = *non_edges.iter().next().unwrap();
        non_edges.remove(&uv);
        println!("{} {}", uv.0, uv.1);
    }
}
