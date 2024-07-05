use std::collections::HashSet;

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i32, i32);

fn visited_houses(xs: &[u8]) -> HashSet<Crd> {
    let mut crd = Crd(0, 0);
    let mut visited: HashSet<Crd> = HashSet::from([crd]);

    for x in xs {
        let Crd(ro, co) = crd;
        crd = match x {
            b'^' => Crd(ro - 1, co),
            b'>' => Crd(ro, co + 1),
            b'v' => Crd(ro + 1, co),
            b'<' => Crd(ro, co - 1),
            _ => panic!("Invalid direction code {}", x),
        };
        visited.insert(crd);
    }
    visited
}

fn main() {
    let xs: Vec<u8> = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .to_owned()
        .into_bytes();

    println!("{}", visited_houses(&xs).len());

    let a = visited_houses(&xs.iter().step_by(2).copied().collect::<Vec<_>>());
    let b = visited_houses(&xs.iter().skip(1).step_by(2).copied().collect::<Vec<_>>());
    println!("{}", a.union(&b).collect::<HashSet<_>>().len());
}
