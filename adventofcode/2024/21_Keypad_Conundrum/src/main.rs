use std::{
    collections::HashMap,
    io::{self, BufRead},
};

use itertools::Itertools;

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

fn numpad_program(src: char, dst: char) -> String {
    route(
        crd_in_numpad(' '),
        true,
        crd_in_numpad(src),
        crd_in_numpad(dst),
    )
}

fn arrpad_program(src: char, dst: char) -> String {
    route(
        crd_in_arrpad(' '),
        true,
        crd_in_arrpad(src),
        crd_in_arrpad(dst),
    )
}

fn arrpad_metaprogram(xs: &str) -> String {
    std::iter::once('A')
        .chain(xs.chars())
        .collect::<Vec<_>>()
        .windows(2)
        .fold(String::new(), |mut acc, uv| {
            let [u, v] = uv else { panic!() };
            acc += &arrpad_program(*u, *v);
            acc.push('A');
            acc
        })
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

fn evolve(subs: &HashMap<String, String>, fqs: &HashMap<String, usize>) -> HashMap<String, usize> {
    let mut new_fqs: HashMap<String, usize> = HashMap::new();
    for (s, f) in fqs {
        if !subs.contains_key(s) {
            eprintln!("subs[{}]", s);
        }
        let t = subs.get(s).unwrap();
        for x in apress_tokens(t) {
            new_fqs.entry(x).and_modify(|g| *g += f).or_insert(*f);
        }
    }
    new_fqs
}

fn total_length(fqs: &HashMap<String, usize>) -> usize {
    fqs.iter().map(|(k, v)| k.len() * v).sum()
}

fn end_length(intermediaries_num: usize, subs: &HashMap<String, String>, p: &str) -> usize {
    let mut fqs: HashMap<String, usize> = apress_tokens(p).into_iter().counts();
    eprintln!("{} p:{} fqs:{:?}", p.len(), p, fqs);
    for t in 1..=intermediaries_num {
        fqs = evolve(subs, &fqs);
        eprintln!("t:{} {}", t, total_length(&fqs));
    }
    total_length(&fqs)
}

fn main() {
    let numpad_codes: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().to_string())
        .collect();

    // let subs: HashMap<String, String> = [
    //     "A", "^A", "^^>A", "<A", "vvvA", ">>^A", ">A", "^>A", "v<A", "v>A", "v<<A", "^^^A", "vA",
    //     ">>A", "^^A", "^<<A", "^^<<A", "vvA", ">^^A", ">^A", "<vA", "<^A", "<<^^A", ">>vA", "<<^A",
    //     ">vA", "<^^^A", ">vvvA", ">vvA", "^<A", "^^^<A", "vv>A",
    // ]
    // .into_iter()
    // .map(|s| (s.to_string(), arrpad_metaprogram(s)))
    // .map(|(a, b)| (a.to_string(), b.to_string()))
    // .collect();

    let subs: HashMap<String, String> = [
        // inA
        ("A", "A"),
        ("^A", "<A>A"),
        ("<A", "v<<A>>^A"),
        (">^^A", "vA^<AA>A"),
        ("vvvA", "v<AAA>^A"),
        (">>^A", "vAA^<A>A"),
        ("v<<A", "v<A<AA>>^A"),
        ("vA", "v<A>^A"),
        ("^<A", "<Av<A>>^A"),
        (">A", "vA^A"),
        (">^A", "vA^<A>A"),
        ("v<A", "v<A<A>>^A"),
        ("^^^A", "<AAA>A"),
        (">>A", "vAA^A"),
        ("^^A", "<AA>A"),
        ("^<<A", "<Av<AA>>^A"),
        ("^^<<A", "<AAv<AA>>^A"),
        ("vvA", "v<AA>^A"),
        ("<<^^A", "v<<AA>^AA>A"),
        // in1
        ("<<^A", "v<<AA>^A>A"),
        (">>vA", "vAA<A>^A"),
        ("<^^^A", "v<<A>^AAA>A"),
        (">vvvA", "vA<AAA>^A"),
        (">vvA", "vA<AA>^A"),
        ("<^A", "v<<A>^A>A"),
    ]
    .into_iter()
    .map(|(a, b)| (a.to_string(), b.to_string()))
    .collect();

    let mut result: usize = 0;
    for code in numpad_codes.iter() {
        let p: String = std::iter::once('A')
            .chain(code.chars())
            .collect::<Vec<_>>()
            .windows(2)
            .fold(String::new(), |mut acc, uv| {
                let [u, v] = uv else { panic!() };
                acc += &numpad_program(*u, *v);
                acc.push('A');
                acc
            });
        result += end_length(2, &subs, &p) * code[0..code.len() - 1].parse::<usize>().unwrap();
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
    fn numpad_program_works() {
        assert_eq!(numpad_program('1', '0'), ">v");
        assert_eq!(numpad_program('A', '9'), "^^^");
    }

    #[test]
    fn arrpad_program_works() {
        assert_eq!(arrpad_program('<', '^'), ">^");
        assert_eq!(arrpad_program('A', '<'), "v<<");
    }

    #[test]
    fn arrpad_metaprogram_works() {
        assert_eq!(arrpad_metaprogram("<A"), "v<<A>>^A");
        assert_eq!(arrpad_metaprogram("A"), "A");
    }
}
