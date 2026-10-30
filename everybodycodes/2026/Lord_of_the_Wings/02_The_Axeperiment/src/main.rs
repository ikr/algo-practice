use itertools::Itertools;
use std::{
    collections::VecDeque,
    io::{BufRead, stdin},
};

const V_NUM: usize = 10;

fn decode_relation(s: &str) -> (usize, usize) {
    assert_eq!(s.len(), 3);
    let xs: Vec<_> = s.bytes().collect();

    let pair: [usize; 2] = [xs[0], xs[2]]
        .into_iter()
        .map(|x| (x - b'0') as usize)
        .collect::<Vec<_>>()
        .try_into()
        .unwrap();

    match xs[1] {
        b'<' => (pair[1], pair[0]),
        b'>' => (pair[0], pair[1]),
        _ => unreachable!(),
    }
}

fn decode_group(s: &str) -> Vec<(usize, usize)> {
    s.split(' ').map(decode_relation).collect()
}

fn group_graph(group: &[(usize, usize)]) -> Vec<Vec<usize>> {
    group
        .iter()
        .fold(vec![vec![]; V_NUM], |mut graph, &(u, v)| {
            graph[u].push(v);
            graph
        })
}

fn toposort(graph: Vec<Vec<usize>>) -> Vec<usize> {
    let mut indeg: [usize; V_NUM] = graph.iter().fold([0; V_NUM], |mut agg, vs| {
        for &v in vs {
            agg[v] += 1;
        }
        agg
    });

    let mut q: VecDeque<usize> = indeg
        .iter()
        .enumerate()
        .filter_map(|(u, &d)| (d == 0).then_some(u))
        .collect();

    let mut result = vec![];

    while let Some(u) = q.pop_front() {
        result.push(u);

        for &v in &graph[u] {
            indeg[v] -= 1;

            if indeg[v] == 0 {
                q.push_back(v);
            }
        }
    }

    result
}

fn number_from_digits(ds: Vec<usize>) -> usize {
    ds.into_iter()
        .rev()
        .fold((0, 1), |(agg, m), d| (agg + d * m, m * 10))
        .0
}

fn unique_vs(group: Vec<(usize, usize)>) -> Vec<usize> {
    group
        .into_iter()
        .flat_map(|(u, v)| vec![u, v])
        .unique()
        .collect()
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let groups: Vec<_> = lines.into_iter().map(|s| decode_group(&s)).collect();
    let graphs: Vec<_> = groups.iter().map(|group| group_graph(group)).collect();

    let results: Vec<usize> = graphs
        .into_iter()
        .zip(groups.into_iter().map(unique_vs))
        .map(|(g, vs)| {
            let ds: Vec<_> = toposort(g).into_iter().filter(|u| vs.contains(u)).collect();
            number_from_digits(ds)
        })
        .collect();

    println!("{}", results.into_iter().sum::<usize>());
}
