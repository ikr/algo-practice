use ac_library::Dsu;
use itertools::{
    Itertools,
    MinMaxResult::{MinMax, NoElements, OneElement},
};
use std::{
    collections::VecDeque,
    io::{BufRead, stdin},
};

#[derive(Clone, Copy, PartialEq)]
struct Crd(i16, i16);

impl Crd {
    fn adjacent(self) -> Vec<Crd> {
        let Crd(ro, co) = self;

        vec![
            Crd(ro - 1, co),
            Crd(ro, co + 1),
            Crd(ro + 1, co),
            Crd(ro, co - 1),
        ]
    }
}

fn clusters(ps: Vec<Crd>) -> Vec<Vec<Crd>> {
    let mut dsu: Dsu = ps
        .iter()
        .enumerate()
        .fold(Dsu::new(ps.len()), |mut agg, (u, &roco)| {
            for pq in roco.adjacent() {
                if let Some(v) = ps.iter().position(|&xy| xy == pq) {
                    agg.merge(u, v);
                }
            }
            agg
        });

    dsu.groups()
        .into_iter()
        .map(|group| group.into_iter().map(|i| ps[i]).collect())
        .collect()
}

fn top_bottom(ps: &[Crd]) -> (i16, i16) {
    match ps.iter().map(|Crd(ro, _)| *ro).minmax() {
        MinMax(a, b) => (a, b),
        OneElement(a) => (a, a),
        NoElements => panic!(),
    }
}

fn left_right(ps: &[Crd]) -> (i16, i16) {
    match ps.iter().map(|Crd(_, co)| *co).minmax() {
        MinMax(a, b) => (a, b),
        OneElement(a) => (a, a),
        NoElements => panic!(),
    }
}

fn l_shaped_cluster_ray_coverage_size(cluster: &[Crd]) -> Option<i16> {
    let (top, bottom) = top_bottom(cluster);
    let (left, right) = left_right(cluster);

    let corners = [
        Crd(top, left),
        Crd(top, right),
        Crd(bottom, right),
        Crd(bottom, left),
    ];

    corners
        .iter()
        .position(|p| !cluster.contains(p))
        .map(|i_empty_point| {
            let i_opposite_point = (i_empty_point + 2) % corners.len();
            let Crd(e_ro, e_co) = corners[i_empty_point];
            let Crd(o_ro, o_co) = corners[i_opposite_point];
            let dro = (o_ro - e_ro).signum();
            let dco = (o_co - e_co).signum();

            let (mut ro, mut co) = (e_ro, e_co);

            while !cluster.contains(&Crd(ro, e_co)) {
                ro += dro;
            }

            while !cluster.contains(&Crd(e_ro, co)) {
                co += dco;
            }

            let inner_height: i16 = ro.abs_diff(o_ro) as i16 + 1;
            let inner_width: i16 = co.abs_diff(o_co) as i16 + 1;

            (inner_width + inner_height)
                .min(bottom - top + 1)
                .min(right - left + 1)
        })
}

fn flood_fill(walls: &[Crd], source: Crd) -> Vec<Crd> {
    let mut result = vec![source];
    let mut q = VecDeque::from([source]);

    while let Some(u) = q.pop_front() {
        for v in u.adjacent() {
            if !result.contains(&v) && !walls.contains(&v) {
                result.push(v);
                q.push_back(v);
            }
        }
    }

    result
}

fn tor_cluster_ray_coverage_size(cluster: &[Crd]) -> Option<i16> {
    let (top, bottom) = top_bottom(cluster);
    let (left, right) = left_right(cluster);

    (top..bottom)
        .cartesian_product(left..right)
        .find(|&(ro, co)| !cluster.contains(&Crd(ro, co)))
        .map(|(e_ro, e_co)| {
            let inner_space = flood_fill(&cluster, Crd(e_ro, e_co));
            let (inner_top, inner_bottom) = top_bottom(&inner_space);
            let (inner_left, inner_right) = left_right(&inner_space);
            let abcd = [
                inner_top - top,
                right - inner_right,
                bottom - inner_bottom,
                inner_left - left,
            ];
            assert!(abcd.iter().all(|&x| x > 0));

            abcd.into_iter()
                .sum::<i16>()
                .min(bottom - top + 1)
                .min(right - left + 1)
        })
}

fn rect_cluster_ray_coverage_size(cluster: &[Crd]) -> i16 {
    let (top, bottom) = top_bottom(cluster);
    let (left, right) = left_right(cluster);
    (bottom - top).min(right - left) + 1
}

fn main() {
    let grid: Vec<Vec<u8>> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().bytes().collect())
        .collect();

    let magma: Vec<Crd> = grid
        .into_iter()
        .enumerate()
        .flat_map(move |(i, row)| {
            row.into_iter()
                .enumerate()
                .filter_map(move |(j, x)| (x == b'#').then_some(Crd(i as i16, j as i16)))
        })
        .collect();

    let cs = clusters(magma);
    let result: i16 = cs
        .into_iter()
        .map(|ctr| {
            l_shaped_cluster_ray_coverage_size(&ctr)
                .or_else(|| tor_cluster_ray_coverage_size(&ctr))
                .unwrap_or_else(|| rect_cluster_ray_coverage_size(&ctr))
        })
        .sum();
    println!("{result}");
}
