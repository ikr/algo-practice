use ac_library::Dsu;
use itertools::{
    Itertools,
    MinMaxResult::{MinMax, NoElements, OneElement},
};
use std::io::{BufRead, stdin};

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
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

fn l_cluster_ray_coverage_size(cluster: Vec<Crd>) -> i16 {
    let (top, bottom) = top_bottom(&cluster);
    let (left, right) = left_right(&cluster);

    let corners = [
        Crd(top, left),
        Crd(top, right),
        Crd(bottom, right),
        Crd(bottom, left),
    ];

    if let Some(i_empty_point) = corners.iter().position(|p| !cluster.contains(p)) {
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
    } else {
        (bottom - top).min(right - left) + 1
    }
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
    let result: i16 = cs.into_iter().map(l_cluster_ray_coverage_size).sum();
    println!("{result}");
}
