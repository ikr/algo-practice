use std::{
    collections::HashMap,
    io::{self, BufRead},
};

use itertools::Itertools;
use rand::prelude::SliceRandom;
use rand::thread_rng;

type Freqs = HashMap<String, usize>;

const NUMPAD: [[char; 3]; 4] = [
    ['7', '8', '9'],
    ['4', '5', '6'],
    ['1', '2', '3'],
    [' ', '0', 'A'],
];

const ARRPAD: [[char; 3]; 2] = [[' ', '^', 'A'], ['<', 'v', '>']];

fn crd_of(grid: &[[char; 3]], c: char) -> (usize, usize) {
    for (i, row) in grid.iter().enumerate() {
        for (j, cell) in row.iter().enumerate() {
            if *cell == c {
                return (i, j);
            }
        }
    }
    panic!()
}

fn crd_in_numpad(c: char) -> (usize, usize) {
    crd_of(&NUMPAD, c)
}

fn crd_in_arrpad(c: char) -> (usize, usize) {
    crd_of(&ARRPAD, c)
}

fn route_crds(src: (usize, usize), route: &str) -> Vec<(usize, usize)> {
    std::iter::once(src)
        .chain(route.chars().scan(src, |cur, x| {
            match x {
                '^' => cur.0 -= 1,
                '>' => cur.1 += 1,
                'v' => cur.0 += 1,
                '<' => cur.1 -= 1,
                _ => panic!(),
            }
            Some(*cur)
        }))
        .collect()
}

fn vert_first_route(src: (usize, usize), dst: (usize, usize)) -> String {
    let (r, c) = dst;
    let mut result = String::new();
    let mut cur = src;

    while cur != dst {
        let (i, j) = cur;
        if i < r {
            cur.0 += 1;
            result.push('v');
        } else if i > r {
            cur.0 -= 1;
            result.push('^');
        } else if j < c {
            cur.1 += 1;
            result.push('>');
        } else {
            assert!(j > c);
            cur.1 -= 1;
            result.push('<');
        }
    }

    result
}

fn horz_first_route(src: (usize, usize), dst: (usize, usize)) -> String {
    let (r, c) = dst;
    let mut result = String::new();
    let mut cur = src;

    while cur != dst {
        let (i, j) = cur;
        if j < c {
            cur.1 += 1;
            result.push('>');
        } else if j > c {
            cur.1 -= 1;
            result.push('<');
        } else if i < r {
            cur.0 += 1;
            result.push('v');
        } else {
            assert!(i > r);
            cur.0 -= 1;
            result.push('^');
        }
    }

    result
}

fn route(
    forbidden: (usize, usize),
    favor_horz: bool,
    src: (usize, usize),
    dst: (usize, usize),
) -> String {
    assert_ne!(src, forbidden);
    assert_ne!(dst, forbidden);

    let mut opts = [vert_first_route(src, dst), horz_first_route(src, dst)];
    if favor_horz {
        opts.reverse();
    }

    opts.into_iter()
        .find(|xs| {
            let crds = route_crds(src, xs);
            !crds.contains(&forbidden)
        })
        .unwrap()
}

fn numpad_route_variants(src: char, dst: char) -> Vec<String> {
    let v = route(
        crd_in_numpad(' '),
        false,
        crd_in_numpad(src),
        crd_in_numpad(dst),
    );
    let h = route(
        crd_in_numpad(' '),
        true,
        crd_in_numpad(src),
        crd_in_numpad(dst),
    );
    [v, h].into_iter().unique().collect()
}

fn arrpad_route_variants(src: char, dst: char) -> Vec<String> {
    let v = route(
        crd_in_arrpad(' '),
        false,
        crd_in_arrpad(src),
        crd_in_arrpad(dst),
    );
    let h = route(
        crd_in_arrpad(' '),
        true,
        crd_in_arrpad(src),
        crd_in_arrpad(dst),
    );
    [v, h].into_iter().unique().collect()
}

fn arrpad_metaprograms(xs: &str) -> Vec<String> {
    let mut ps: Vec<String> = vec![String::new()];

    for (u, v) in std::iter::once('A').chain(xs.chars()).tuple_windows() {
        let mut qs: Vec<String> = vec![];
        for pref in ps.iter() {
            for suff in arrpad_route_variants(u, v) {
                let p = pref.clone() + &suff + "A";
                qs.push(p)
            }
        }
        ps = qs;
    }

    ps
}

fn positions_of(xs: &str, x0: char, lim: usize) -> Vec<usize> {
    xs.chars()
        .enumerate()
        .filter_map(|(i, x)| if x == x0 { Some(i) } else { None })
        .take(lim)
        .collect()
}

fn apress_tokens(s: &str) -> Vec<String> {
    let mut ais: Vec<usize> = vec![usize::MAX];
    ais.extend(positions_of(s, 'A', usize::MAX));
    ais.windows(2)
        .map(|ij| {
            let i = ij[0];
            let j = ij[1];
            if i == usize::MAX {
                s[0..j + 1].to_string()
            } else {
                s[i + 1..j + 1].to_string()
            }
        })
        .collect()
}

fn evolve_one(fq0: &Freqs) -> Vec<Freqs> {
    let mut result: Vec<Freqs> = vec![HashMap::new()];

    for (s0, f0) in fq0 {
        let mut new_result: Vec<Freqs> = vec![];

        for unsplit_variant in arrpad_metaprograms(s0) {
            let mut fqs = result.clone();
            for token in apress_tokens(&unsplit_variant) {
                for fq in fqs.iter_mut() {
                    fq.entry(token.clone())
                        .and_modify(|f| *f += f0)
                        .or_insert(*f0);
                }
            }
            new_result.extend(fqs);
        }

        result = new_result;
    }
    result
}

fn evolve(fqs: &[Freqs]) -> Vec<Freqs> {
    let mut result: Vec<Freqs> = vec![];
    for fq in fqs {
        result.extend(evolve_one(fq));
    }
    result
}

fn total_length(fqs: &Freqs) -> usize {
    fqs.iter().map(|(k, v)| k.len() * v).sum()
}

fn prune(t: usize, fqs: Vec<Freqs>) -> Vec<Freqs> {
    let mut rng = thread_rng();
    let report = fqs
        .iter()
        .map(total_length)
        .counts()
        .into_iter()
        .sorted()
        .collect::<Vec<_>>();

    eprintln!("{:?}", report);

    if t > 2 {
        let mut top: Vec<Freqs> = fqs
            .into_iter()
            .filter(|fq| {
                let tl = total_length(&fq);
                tl == report[0].0 //|| tl == report[1].0 || tl == report[2].0
            })
            .collect();
        top.shuffle(&mut rng);
        top.into_iter().take(30_000).collect()
    } else {
        fqs
    }
}

fn end_length(intermediaries_num: usize, mut fqs: Vec<Freqs>) -> usize {
    for t in 1..=intermediaries_num {
        eprintln!("t:{}", t);
        fqs = prune(t, evolve(&fqs));
    }
    fqs.into_iter().map(|fq| total_length(&fq)).min().unwrap()
}

fn main() {
    let numpad_codes: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().to_string())
        .collect();

    let mut result: usize = 0;
    for code in numpad_codes.iter() {
        let ps: Vec<String> = std::iter::once('A')
            .chain(code.chars())
            .collect::<Vec<_>>()
            .windows(2)
            .fold(vec!["".to_string()], |acc, uv| {
                let [u, v] = uv else { panic!() };
                let mut qs: Vec<String> = vec![];

                for pref in acc.iter() {
                    for suff in numpad_route_variants(*u, *v) {
                        let p = pref.clone() + &suff + "A";
                        qs.push(p)
                    }
                }
                qs
            });

        let fqs: Vec<Freqs> = ps
            .iter()
            .map(|p| apress_tokens(p).into_iter().counts())
            .collect();

        result += end_length(25, fqs) * code[0..code.len() - 1].parse::<usize>().unwrap();
    }
    println!("{}", result);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn apress_tokens_works_0() {
        assert!(apress_tokens("").is_empty());
    }

    #[test]
    fn apress_tokens_works_1() {
        assert_eq!(apress_tokens("A"), vec!["A"]);
        assert_eq!(apress_tokens("AA"), vec!["A", "A"]);
    }

    #[test]
    fn apress_tokens_works_2() {
        assert_eq!(
            apress_tokens("<A^A>^^AvvvA"),
            vec!["<A", "^A", ">^^A", "vvvA"]
        )
    }

    #[test]
    fn route_crds_works() {
        assert_eq!(
            route_crds((1, 1), "^>vv<^"),
            vec![(1, 1), (0, 1), (0, 2), (1, 2), (2, 2), (2, 1), (1, 1)]
        );
    }

    #[test]
    fn vert_first_route_works() {
        assert_eq!(vert_first_route((3, 3), (5, 1)), "vv<<");
    }

    #[test]
    fn horz_first_route_works() {
        assert_eq!(horz_first_route((3, 3), (1, 5)), ">>^^");
    }

    #[test]
    fn numpad_route_variants_works() {
        assert_eq!(numpad_route_variants('1', '0'), vec![">v"]);
        assert_eq!(numpad_route_variants('2', '9'), vec!["^^>", ">^^"]);
    }

    #[test]
    fn arrpad_route_variants_works() {
        assert_eq!(arrpad_route_variants('<', '^'), vec![">^"]);
        assert_eq!(arrpad_route_variants('v', 'A'), vec!["^>", ">^"]);
    }

    #[test]
    fn arrpad_metaprogram_works() {
        assert_eq!(arrpad_metaprograms("<A"), vec!["v<<A>>^A"]);
        assert_eq!(arrpad_metaprograms("A"), vec!["A"]);
        assert_eq!(arrpad_metaprograms("^>A"), vec!["<Av>A^A", "<A>vA^A"]);
        assert_eq!(
            arrpad_metaprograms("^>A^>A"),
            vec![
                "<Av>A^A<Av>A^A",
                "<Av>A^A<A>vA^A",
                "<A>vA^A<Av>A^A",
                "<A>vA^A<A>vA^A"
            ]
        );
    }

    #[test]
    fn evolve_one_works() {
        assert_eq!(
            evolve_one(&HashMap::from([("A".to_string(), 1)])),
            vec![HashMap::from([("A".to_string(), 1)])]
        );
        assert_eq!(
            evolve_one(&HashMap::from([("^>A".to_string(), 2)])),
            vec![
                HashMap::from([
                    ("<A".to_string(), 2),
                    ("v>A".to_string(), 2),
                    ("^A".to_string(), 2),
                ]),
                HashMap::from([
                    ("<A".to_string(), 2),
                    (">vA".to_string(), 2),
                    ("^A".to_string(), 2),
                ])
            ]
        );
    }
}
