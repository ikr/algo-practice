use proconio::input;
use std::{
    collections::HashSet,
    io::{self, BufWriter, Write},
};

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i32, i32);

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

fn solve(rc0: Crd, dirs: &[char]) -> String {
    let mut head = Crd(0, 0);
    let mut sensor = rc0;
    let mut smoke: HashSet<Crd> = HashSet::from([Crd(0, 0)]);
    let mut result: String = String::new();

    for &d in dirs.iter() {
        let delta = match d {
            'N' => Crd(1, 0),
            'E' => Crd(0, -1),
            'S' => Crd(-1, 0),
            'W' => Crd(0, 1),
            _ => panic!("Unknown dir {}", d),
        };

        head = head + delta;
        sensor = sensor + delta;
        smoke.insert(head);
        result.push(if smoke.contains(&sensor) { '1' } else { '0' });
    }

    result
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        r: i32,
        c: i32,
        dirs: String,
    }

    let cs: Vec<char> = dirs.chars().collect();
    assert_eq!(cs.len(), n);

    let result = solve(Crd(r, c), &cs);
    writeln!(writer, "{}", result).unwrap();
    writer.flush().unwrap();
}
