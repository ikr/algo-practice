use std::collections::HashSet;

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i32, i32);

fn main() {
    let xs: Vec<u8> = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .to_owned()
        .into_bytes();

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

    println!("{}", visited.len());
}
