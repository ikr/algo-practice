use std::{
    collections::HashMap,
    io::{self, BufRead},
};

use itertools::Itertools;

type Freq = HashMap<String, usize>;

const NUMPAD: [[char; 3]; 4] = [
    ['7', '8', '9'],
    ['4', '5', '6'],
    ['1', '2', '3'],
    [' ', '0', 'A'],
];

const ARRPAD: [[char; 3]; 2] = [[' ', '^', 'A'], ['<', 'v', '>']];

const BRANCHING_TRANSITIONS: [&str; 6] = ["^>", ">^", "vA", "Av", "<A", "A<"];

fn branching_index(src: char, dst: char) -> Option<usize> {
    let t: String = [src, dst].into_iter().collect();
    BRANCHING_TRANSITIONS.iter().position(|&s| s == t)
}

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

fn total_length(fqs: &Freq) -> usize {
    fqs.iter().map(|(k, v)| k.len() * v).sum()
}

fn evolve(branching_bits: u8, fq0: Freq) -> Freq {
    let mut result: Freq = HashMap::new();

    for (s0, f0) in fq0 {
        for (u, v) in std::iter::once('A').chain(s0.chars()).tuple_windows() {
            let favor_horz = if let Some(i) = branching_index(u, v) {
                (1u8 << i) & branching_bits == 0
            } else {
                true
            };

            let w = route(
                crd_in_arrpad(' '),
                favor_horz,
                crd_in_arrpad(u),
                crd_in_arrpad(v),
            ) + "A";

            result.entry(w).and_modify(|f| *f += f0).or_insert(f0);
        }
    }
    result
}

fn metaprogram_complexity(code: &str, num_layers: u8, p: &str) -> usize {
    let fq0 = apress_tokens(p).into_iter().counts();

    let mut result = usize::MAX;
    let m = BRANCHING_TRANSITIONS.len() as u8;

    for branching_bits in 0..(1 << m) {
        let mut fq = fq0.clone();
        for _ in 0..num_layers {
            fq = evolve(branching_bits, fq);
        }

        result = result.min(total_length(&fq));
    }

    result * code[0..code.len() - 1].parse::<usize>().unwrap()
}

fn numpad_code_complexity(code: String) -> usize {
    let numpad_code_programs: Vec<String> = std::iter::once('A')
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

    numpad_code_programs
        .into_iter()
        .map(|p| metaprogram_complexity(&code, 25, &p))
        .min()
        .unwrap()
}

fn main() {
    let numpad_codes: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().to_string())
        .collect();

    let result: usize = numpad_codes.into_iter().map(numpad_code_complexity).sum();
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
}
