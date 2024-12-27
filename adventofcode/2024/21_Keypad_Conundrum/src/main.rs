use std::{
    collections::HashMap,
    hash::Hash,
    io::{self, BufRead},
};

use itertools::Itertools;

#[derive(Clone, Copy, Debug, Hash, Eq, PartialEq)]
enum Dir {
    N,
    E,
    S,
    W,
}

#[derive(Clone, Copy, Debug, PartialEq)]
enum NumKey {
    N0,
    N1,
    N2,
    N3,
    N4,
    N5,
    N6,
    N7,
    N8,
    N9,
    A,
}

impl NumKey {
    fn parse(c: char) -> Self {
        match c {
            '0' => NumKey::N0,
            '1' => NumKey::N1,
            '2' => NumKey::N2,
            '3' => NumKey::N3,
            '4' => NumKey::N4,
            '5' => NumKey::N5,
            '6' => NumKey::N6,
            '7' => NumKey::N7,
            '8' => NumKey::N8,
            '9' => NumKey::N9,
            'A' => NumKey::A,
            _ => panic!("Invalid numpad key source `{}`", c),
        }
    }

    fn numeric_value(&self) -> usize {
        let os: Vec<char> = ('0'..='9').collect();
        os.into_iter()
            .position(|c| *self == Self::parse(c))
            .unwrap()
    }

    fn transitions(&self, to: NumKey) -> Vec<Vec<Dir>> {
        match (self, to) {
            (NumKey::N0, NumKey::N0) => vec![],
            (NumKey::N0, NumKey::N1) => vec![vec![Dir::N, Dir::W]],
            (NumKey::N0, NumKey::N2) => vec![vec![Dir::N]],
            (NumKey::N0, NumKey::N3) => unique_permutations(&[Dir::N, Dir::E]),
            (NumKey::N0, NumKey::N4) => push_front(Dir::N, unique_permutations(&[Dir::N, Dir::W])),
            (NumKey::N0, NumKey::N5) => vec![vec![Dir::N, Dir::N]],
            (NumKey::N0, NumKey::N6) => unique_permutations(&[Dir::N, Dir::N, Dir::E]),
            (NumKey::N0, NumKey::N7) => {
                push_front(Dir::N, unique_permutations(&[Dir::N, Dir::N, Dir::W]))
            }

            (NumKey::N0, NumKey::N8) => vec![vec![Dir::N, Dir::N, Dir::N]],
            (NumKey::N0, NumKey::N9) => unique_permutations(&[Dir::N, Dir::N, Dir::N, Dir::E]),
            (NumKey::N0, NumKey::A) => vec![vec![Dir::E]],

            (NumKey::N1, NumKey::N0) => vec![vec![Dir::E, Dir::S]],
            (NumKey::N1, NumKey::N1) => vec![],
            (NumKey::N1, NumKey::N2) => vec![vec![Dir::E]],
            (NumKey::N1, NumKey::N3) => vec![vec![Dir::E, Dir::E]],
            (NumKey::N1, NumKey::N4) => vec![vec![Dir::N]],
            (NumKey::N1, NumKey::N5) => unique_permutations(&[Dir::N, Dir::E]),
            (NumKey::N1, NumKey::N6) => unique_permutations(&[Dir::N, Dir::E, Dir::E]),
            (NumKey::N1, NumKey::N7) => vec![vec![Dir::N, Dir::N]],
            (NumKey::N1, NumKey::N8) => unique_permutations(&[Dir::N, Dir::N, Dir::E]),
            (NumKey::N1, NumKey::N9) => unique_permutations(&[Dir::N, Dir::N, Dir::E, Dir::E]),
            (NumKey::N1, NumKey::A) => push_front(Dir::E, unique_permutations(&[Dir::S, Dir::E])),

            (NumKey::N2, NumKey::N0) => vec![vec![Dir::S]],
            (NumKey::N2, NumKey::N1) => vec![vec![Dir::W]],
            (NumKey::N2, NumKey::N2) => vec![],
            (NumKey::N2, NumKey::N3) => vec![vec![Dir::E]],
            (NumKey::N2, NumKey::N4) => unique_permutations(&[Dir::N, Dir::W]),
            (NumKey::N2, NumKey::N5) => vec![vec![Dir::N]],
            (NumKey::N2, NumKey::N6) => unique_permutations(&[Dir::N, Dir::E]),
            (NumKey::N2, NumKey::N7) => unique_permutations(&[Dir::N, Dir::N, Dir::W]),
            (NumKey::N2, NumKey::N8) => vec![vec![Dir::N, Dir::N]],
            (NumKey::N2, NumKey::N9) => unique_permutations(&[Dir::N, Dir::N, Dir::E]),
            (NumKey::N2, NumKey::A) => unique_permutations(&[Dir::S, Dir::E]),

            (NumKey::N3, NumKey::N0) => unique_permutations(&[Dir::S, Dir::W]),
            (NumKey::N3, NumKey::N1) => vec![vec![Dir::W, Dir::W]],
            (NumKey::N3, NumKey::N2) => vec![vec![Dir::W]],
            (NumKey::N3, NumKey::N3) => vec![],
            (NumKey::N3, NumKey::N4) => unique_permutations(&[Dir::N, Dir::W, Dir::W]),
            (NumKey::N3, NumKey::N5) => unique_permutations(&[Dir::N, Dir::W]),
            (NumKey::N3, NumKey::N6) => vec![vec![Dir::N]],
            (NumKey::N3, NumKey::N7) => unique_permutations(&[Dir::N, Dir::N, Dir::W, Dir::W]),
            (NumKey::N3, NumKey::N8) => unique_permutations(&[Dir::N, Dir::N, Dir::W]),
            (NumKey::N3, NumKey::N9) => vec![vec![Dir::N, Dir::N]],
            (NumKey::N3, NumKey::A) => vec![vec![Dir::S]],

            (NumKey::N4, NumKey::N0) => {
                vec![vec![Dir::S, Dir::E, Dir::S], vec![Dir::E, Dir::S, Dir::S]]
            }
            (NumKey::N4, NumKey::N1) => vec![vec![Dir::S]],
            (NumKey::N4, NumKey::N2) => unique_permutations(&[Dir::S, Dir::E]),
            (NumKey::N4, NumKey::N3) => unique_permutations(&[Dir::S, Dir::E, Dir::E]),
            (NumKey::N4, NumKey::N4) => vec![vec![]],
            (NumKey::N4, NumKey::N5) => vec![vec![Dir::E]],
            (NumKey::N4, NumKey::N6) => vec![vec![Dir::E, Dir::E]],
            (NumKey::N4, NumKey::N7) => vec![vec![Dir::N]],
            (NumKey::N4, NumKey::N8) => unique_permutations(&[Dir::N, Dir::E]),
            (NumKey::N4, NumKey::N9) => unique_permutations(&[Dir::N, Dir::E, Dir::E]),
            (NumKey::N4, NumKey::A) => [
                suffix(unique_permutations(&[Dir::S, Dir::E]), vec![Dir::S, Dir::E]),
                push_back(unique_permutations(&[Dir::S, Dir::E, Dir::E]), Dir::S),
            ]
            .concat(),

            (NumKey::N5, NumKey::N0) => vec![vec![Dir::S, Dir::S]],
            (NumKey::N5, NumKey::N1) => unique_permutations(&[Dir::S, Dir::W]),
            (NumKey::N5, NumKey::N2) => vec![vec![Dir::S]],
            (NumKey::N5, NumKey::N3) => unique_permutations(&[Dir::S, Dir::E]),
            (NumKey::N5, NumKey::N4) => vec![vec![Dir::W]],
            (NumKey::N5, NumKey::N5) => vec![],
            (NumKey::N5, NumKey::N6) => vec![vec![Dir::E]],
            (NumKey::N5, NumKey::N7) => unique_permutations(&[Dir::N, Dir::W]),
            (NumKey::N5, NumKey::N8) => vec![vec![Dir::N]],
            (NumKey::N5, NumKey::N9) => unique_permutations(&[Dir::N, Dir::E]),
            (NumKey::N5, NumKey::A) => unique_permutations(&[Dir::S, Dir::S, Dir::E]),

            (NumKey::N6, NumKey::N0) => unique_permutations(&[Dir::S, Dir::S, Dir::W]),
            (NumKey::N6, NumKey::N1) => unique_permutations(&[Dir::S, Dir::W, Dir::W]),
            (NumKey::N6, NumKey::N2) => unique_permutations(&[Dir::S, Dir::W]),
            (NumKey::N6, NumKey::N3) => vec![vec![Dir::S]],
            (NumKey::N6, NumKey::N4) => vec![vec![Dir::W, Dir::W]],
            (NumKey::N6, NumKey::N5) => vec![vec![Dir::W]],
            (NumKey::N6, NumKey::N6) => vec![],
            (NumKey::N6, NumKey::N7) => unique_permutations(&[Dir::N, Dir::W, Dir::W]),
            (NumKey::N6, NumKey::N8) => unique_permutations(&[Dir::N, Dir::W]),
            (NumKey::N6, NumKey::N9) => vec![vec![Dir::N]],
            (NumKey::N6, NumKey::A) => vec![vec![Dir::S, Dir::S]],

            (NumKey::N7, NumKey::N0) => {
                push_back(unique_permutations(&[Dir::S, Dir::S, Dir::E]), Dir::S)
            }
            (NumKey::N7, NumKey::N1) => vec![vec![Dir::S, Dir::S]],
            (NumKey::N7, NumKey::N2) => unique_permutations(&[Dir::S, Dir::S, Dir::E]),
            (NumKey::N7, NumKey::N3) => unique_permutations(&[Dir::S, Dir::S, Dir::E, Dir::E]),
            (NumKey::N7, NumKey::N4) => vec![vec![Dir::S]],
            (NumKey::N7, NumKey::N5) => unique_permutations(&[Dir::S, Dir::E]),
            (NumKey::N7, NumKey::N6) => unique_permutations(&[Dir::S, Dir::E, Dir::E]),
            (NumKey::N7, NumKey::N7) => vec![],
            (NumKey::N7, NumKey::N8) => vec![vec![Dir::E]],
            (NumKey::N7, NumKey::N9) => vec![vec![Dir::E, Dir::E]],
            (NumKey::N7, NumKey::A) => [
                suffix(
                    unique_permutations(&[Dir::S, Dir::S, Dir::E]),
                    vec![Dir::S, Dir::E],
                ),
                push_back(
                    unique_permutations(&[Dir::S, Dir::S, Dir::E, Dir::E]),
                    Dir::S,
                ),
            ]
            .concat(),

            (NumKey::N8, NumKey::N0) => vec![vec![Dir::S, Dir::S, Dir::S]],
            (NumKey::N8, NumKey::N1) => unique_permutations(&[Dir::S, Dir::S, Dir::W]),
            (NumKey::N8, NumKey::N2) => vec![vec![Dir::S, Dir::S]],
            (NumKey::N8, NumKey::N3) => unique_permutations(&[Dir::S, Dir::S, Dir::E]),
            (NumKey::N8, NumKey::N4) => unique_permutations(&[Dir::S, Dir::W]),
            (NumKey::N8, NumKey::N5) => vec![vec![Dir::S]],
            (NumKey::N8, NumKey::N6) => unique_permutations(&[Dir::S, Dir::E]),
            (NumKey::N8, NumKey::N7) => vec![vec![Dir::W]],
            (NumKey::N8, NumKey::N8) => vec![],
            (NumKey::N8, NumKey::N9) => vec![vec![Dir::E]],
            (NumKey::N8, NumKey::A) => unique_permutations(&[Dir::S, Dir::S, Dir::S, Dir::E]),

            (NumKey::N9, NumKey::N0) => unique_permutations(&[Dir::S, Dir::S, Dir::S, Dir::W]),
            (NumKey::N9, NumKey::N1) => unique_permutations(&[Dir::S, Dir::S, Dir::W, Dir::W]),
            (NumKey::N9, NumKey::N2) => unique_permutations(&[Dir::S, Dir::S, Dir::W]),
            (NumKey::N9, NumKey::N3) => vec![vec![Dir::S, Dir::S]],
            (NumKey::N9, NumKey::N4) => unique_permutations(&[Dir::S, Dir::W, Dir::W]),
            (NumKey::N9, NumKey::N5) => unique_permutations(&[Dir::S, Dir::W]),
            (NumKey::N9, NumKey::N6) => vec![vec![Dir::S]],
            (NumKey::N9, NumKey::N7) => vec![vec![Dir::W, Dir::W]],
            (NumKey::N9, NumKey::N8) => vec![vec![Dir::W]],
            (NumKey::N9, NumKey::N9) => vec![],
            (NumKey::N9, NumKey::A) => vec![vec![Dir::S, Dir::S, Dir::S]],

            (NumKey::A, NumKey::N0) => vec![vec![Dir::W]],
            (NumKey::A, NumKey::N1) => push_back(unique_permutations(&[Dir::N, Dir::W]), Dir::W),
            (NumKey::A, NumKey::N2) => unique_permutations(&[Dir::N, Dir::W]),
            (NumKey::A, NumKey::N3) => vec![vec![Dir::N]],
            (NumKey::A, NumKey::N4) => [
                prefix(vec![Dir::W, Dir::N], unique_permutations(&[Dir::N, Dir::W])),
                push_front(Dir::N, unique_permutations(&[Dir::N, Dir::W, Dir::W])),
            ]
            .concat(),
            (NumKey::A, NumKey::N5) => unique_permutations(&[Dir::N, Dir::N, Dir::W]),
            (NumKey::A, NumKey::N6) => vec![vec![Dir::N, Dir::N]],
            (NumKey::A, NumKey::N7) => [
                prefix(
                    vec![Dir::W, Dir::N],
                    unique_permutations(&[Dir::N, Dir::N, Dir::W]),
                ),
                push_front(
                    Dir::N,
                    unique_permutations(&[Dir::N, Dir::N, Dir::W, Dir::W]),
                ),
            ]
            .concat(),
            (NumKey::A, NumKey::N8) => unique_permutations(&[Dir::N, Dir::N, Dir::N, Dir::W]),
            (NumKey::A, NumKey::N9) => vec![vec![Dir::N, Dir::N, Dir::N]],
            (NumKey::A, NumKey::A) => vec![],
        }
    }
}

fn push_front<T: Clone>(what: T, mut xss: Vec<Vec<T>>) -> Vec<Vec<T>> {
    xss.iter_mut().for_each(|xs| xs.insert(0, what.clone()));
    xss
}

fn push_back<T: Clone>(mut xss: Vec<Vec<T>>, what: T) -> Vec<Vec<T>> {
    xss.iter_mut().for_each(|xs| xs.push(what.clone()));
    xss
}

fn prefix<T: Clone>(with: Vec<T>, xss: Vec<Vec<T>>) -> Vec<Vec<T>> {
    xss.into_iter()
        .map(|xs| {
            let mut ys = with.clone();
            ys.extend(xs);
            ys
        })
        .collect()
}

fn suffix<T: Clone>(xss: Vec<Vec<T>>, with: Vec<T>) -> Vec<Vec<T>> {
    xss.into_iter()
        .map(|mut xs| {
            xs.extend(with.clone());
            xs
        })
        .collect()
}

fn unique_permutations<T: Clone + Hash + Eq>(xs: &[T]) -> Vec<Vec<T>> {
    let n = xs.len();
    xs.iter().cloned().permutations(n).unique().collect()
}

#[derive(Clone, Copy, Debug)]
enum ArrKey {
    U,
    R,
    D,
    L,
    A,
}

impl ArrKey {
    fn transitions(&self, to: ArrKey) -> Vec<Vec<Dir>> {
        match (self, to) {
            (ArrKey::U, ArrKey::U) => vec![],
            (ArrKey::U, ArrKey::R) => unique_permutations(&[Dir::S, Dir::E]),
            (ArrKey::U, ArrKey::D) => vec![vec![Dir::S]],
            (ArrKey::U, ArrKey::L) => vec![vec![Dir::S, Dir::W]],
            (ArrKey::U, ArrKey::A) => vec![vec![Dir::E]],

            (ArrKey::R, ArrKey::U) => unique_permutations(&[Dir::N, Dir::W]),
            (ArrKey::R, ArrKey::R) => vec![],
            (ArrKey::R, ArrKey::D) => vec![vec![Dir::W]],
            (ArrKey::R, ArrKey::L) => vec![vec![Dir::W, Dir::W]],
            (ArrKey::R, ArrKey::A) => vec![vec![Dir::N]],

            (ArrKey::D, ArrKey::U) => vec![vec![Dir::N]],
            (ArrKey::D, ArrKey::R) => vec![vec![Dir::E]],
            (ArrKey::D, ArrKey::D) => vec![],
            (ArrKey::D, ArrKey::L) => vec![vec![Dir::W]],
            (ArrKey::D, ArrKey::A) => unique_permutations(&[Dir::N, Dir::E]),

            (ArrKey::L, ArrKey::U) => vec![vec![Dir::E, Dir::N]],
            (ArrKey::L, ArrKey::R) => vec![vec![Dir::E, Dir::E]],
            (ArrKey::L, ArrKey::D) => vec![vec![Dir::E]],
            (ArrKey::L, ArrKey::L) => vec![],
            (ArrKey::L, ArrKey::A) => push_front(Dir::E, unique_permutations(&[Dir::N, Dir::E])),

            (ArrKey::A, ArrKey::U) => vec![vec![Dir::W]],
            (ArrKey::A, ArrKey::R) => vec![vec![Dir::S]],
            (ArrKey::A, ArrKey::D) => unique_permutations(&[Dir::S, Dir::W]),
            (ArrKey::A, ArrKey::L) => push_back(unique_permutations(&[Dir::S, Dir::W]), Dir::W),
            (ArrKey::A, ArrKey::A) => vec![],
        }
    }

    fn from_dir(dir: Dir) -> Self {
        match dir {
            Dir::N => ArrKey::U,
            Dir::E => ArrKey::R,
            Dir::S => ArrKey::D,
            Dir::W => ArrKey::L,
        }
    }

    fn symbol(&self) -> char {
        match self {
            ArrKey::U => '^',
            ArrKey::R => '>',
            ArrKey::D => 'v',
            ArrKey::L => '<',
            ArrKey::A => 'A',
        }
    }
}

fn stringify(ks: &[ArrKey]) -> String {
    ks.iter().map(ArrKey::symbol).collect()
}

fn parse_numpad_code(s: &str) -> Vec<NumKey> {
    s.chars().map(NumKey::parse).collect()
}

fn numeric_value(nks: &[NumKey]) -> usize {
    nks.iter()
        .filter_map(|&nk| {
            if nk == NumKey::A {
                None
            } else {
                Some(nk.numeric_value())
            }
        })
        .fold(0, |acc, x| acc * 10 + x)
}

fn arrpad_programs_for_given_code(code: &[NumKey]) -> Vec<Vec<ArrKey>> {
    let mut programs: Vec<Vec<ArrKey>> = vec![];
    let mut pointing_at = NumKey::A;

    for &x in code {
        let variants = pointing_at.transitions(x);
        if variants.is_empty() {
            programs.iter_mut().for_each(|p| p.push(ArrKey::A));
            continue;
        }

        if programs.is_empty() {
            programs = variants
                .iter()
                .map(|v| {
                    let mut w = v.iter().map(|d| ArrKey::from_dir(*d)).collect::<Vec<_>>();
                    w.push(ArrKey::A);
                    w
                })
                .collect();
        } else {
            programs = programs
                .iter()
                .cartesian_product(variants.iter())
                .map(|(p, v)| {
                    let mut q = p.clone();
                    let mut w = v.iter().map(|d| ArrKey::from_dir(*d)).collect::<Vec<_>>();
                    w.push(ArrKey::A);
                    q.extend(w);
                    q
                })
                .collect();
        }

        pointing_at = x;
    }

    programs
}

fn arrpad_programs_for_given_protoprogram(protoprogram: &[ArrKey]) -> Vec<Vec<ArrKey>> {
    let mut programs: Vec<Vec<ArrKey>> = vec![];
    let mut pointing_at = ArrKey::A;

    for &x in protoprogram {
        let variants = pointing_at.transitions(x);
        if variants.is_empty() {
            programs.iter_mut().for_each(|p| p.push(ArrKey::A));
            continue;
        }

        if programs.is_empty() {
            programs = variants
                .iter()
                .map(|v| {
                    let mut w = v.iter().map(|d| ArrKey::from_dir(*d)).collect::<Vec<_>>();
                    w.push(ArrKey::A);
                    w
                })
                .collect();
        } else {
            programs = programs
                .iter()
                .cartesian_product(variants.iter())
                .map(|(p, v)| {
                    let mut q = p.clone();
                    let mut w = v.iter().map(|d| ArrKey::from_dir(*d)).collect::<Vec<_>>();
                    w.push(ArrKey::A);
                    q.extend(w);
                    q
                })
                .collect();
        }

        pointing_at = x;
    }

    programs
}

fn gather_substiturions_return_optimal_program_for_2_arrpads(
    code: &[NumKey],
) -> (HashMap<String, String>, Vec<ArrKey>) {
    let ps = arrpad_programs_for_given_code(code);
    let qs = ps
        .into_iter()
        .flat_map(|protoprogram| arrpad_programs_for_given_protoprogram(&protoprogram))
        .collect::<Vec<_>>();
    let q0: Vec<ArrKey> = qs
        .iter()
        .min_by_key(|p| (p.len(), stringify(p)))
        .unwrap()
        .to_vec();
    let rs = qs
        .into_iter()
        .flat_map(|protoprogram| arrpad_programs_for_given_protoprogram(&protoprogram))
        .collect::<Vec<_>>();
    let r0: Vec<ArrKey> = rs
        .iter()
        .min_by_key(|p| (p.len(), stringify(p)))
        .unwrap()
        .to_vec();
    (substitutions(&stringify(&q0), &stringify(&r0)), r0)
}

fn positions_of(xs: &str, x0: char, lim: usize) -> Vec<usize> {
    xs.chars()
        .enumerate()
        .filter_map(|(i, x)| if x == x0 { Some(i) } else { None })
        .take(lim)
        .collect()
}

fn substitutions(a: &str, b: &str) -> HashMap<String, String> {
    if a.is_empty() {
        assert!(b.is_empty());
        HashMap::new()
    } else {
        let i0 = positions_of(a, 'A', 1).first().copied().unwrap();
        let j0 = positions_of(b, 'A', i0 + 1).last().copied().unwrap();
        let mut result: HashMap<String, String> =
            HashMap::from([(a[0..i0 + 1].to_string(), b[0..j0 + 1].to_string())]);
        let sub = substitutions(&a[i0 + 1..], &b[j0 + 1..]);
        result.extend(sub);
        result
    }
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
        eprintln!("{:?}", fqs);
        eprintln!("subs[{}]", s);
        let t = subs.get(s).unwrap();
        for x in apress_tokens(t) {
            new_fqs.entry(x).and_modify(|g| *g += f).or_insert(1);
        }
    }
    new_fqs
}

fn end_length(subs: &HashMap<String, String>, p: &str) -> usize {
    let mut fqs: HashMap<String, usize> = apress_tokens(p).into_iter().counts();
    for _ in 3..=25 {
        fqs = evolve(subs, &fqs);
    }
    fqs.into_values().sum()
}

fn main() {
    let numpad_codes: Vec<Vec<NumKey>> = io::stdin()
        .lock()
        .lines()
        .map(|line| parse_numpad_code(&line.unwrap()))
        .collect();

    let mut subs: HashMap<String, String> = HashMap::new();
    let mut result1: usize = 0;
    let mut ps: Vec<String> = vec![];
    for code in numpad_codes.iter() {
        let (subsubs, p) = gather_substiturions_return_optimal_program_for_2_arrpads(code);
        subs.extend(subsubs);
        ps.push(stringify(&p));
        result1 += p.len() * numeric_value(code);
    }
    println!("result1: {}", result1);
    eprintln!("{} {:?}", subs.len(), subs);

    let mut result2: usize = 0;
    for (i, p) in ps.into_iter().enumerate() {
        result2 += end_length(&subs, &p) * numeric_value(&numpad_codes[i]);
    }
    println!("result2: {}", result2);
}

#[cfg(test)]
mod tests {
    use std::collections::HashMap;

    use super::*;

    #[test]
    fn substitutions_function_works() {
        assert_eq!(
            substitutions(
                "v<<A>>^A<A>AvA<^AA>A<vAAA>^A",
                "<vA<AA>>^AvAA<^A>A<v<A>>^AvA^A<vA>^A<v<A>^A>AAvA^A<v<A>A>^AAAvA<^A>A"
            ),
            HashMap::from(
                [
                    ("<A", "<v<A>>^A"),
                    ("<^A", "<v<A>^A>A"),
                    ("<vA", "<v<A>A>^A"),
                    (">>^A", "vAA<^A>A"),
                    (">A", "vA^A"),
                    (">^A", "vA<^A>A"),
                    ("A", "A"),
                    ("v<<A", "<vA<AA>>^A"),
                    ("vA", "<vA>^A"),
                ]
                .map(|(a, b)| (a.to_string(), b.to_string()))
            )
        );
    }

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
}
