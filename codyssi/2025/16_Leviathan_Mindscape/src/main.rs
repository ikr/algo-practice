use std::{
    fmt::Debug,
    io::{BufRead, stdin},
};

#[derive(Clone, Copy, Debug)]
enum Subj {
    Face,
    Row(usize),
    Col(usize),
}

impl Subj {
    fn decode(s: &str) -> Self {
        if s == "FACE" {
            Self::Face
        } else {
            let ab: Vec<_> = s.split_whitespace().collect();
            let i: usize = ab[1].parse().unwrap();
            match ab[0] {
                "ROW" => Self::Row(i),
                "COL" => Self::Col(i),
                _ => panic!("Invalid Subj source `{}`", s),
            }
        }
    }
}

#[derive(Clone, Copy, Debug)]
struct Mutation {
    subj: Subj,
    to_add: u8,
}

impl Mutation {
    fn decode(s: &str) -> Self {
        let ab: Vec<_> = s.split(" - VALUE ").collect();
        let subj = Subj::decode(ab[0]);
        let to_add: u8 = ab[1].parse().unwrap();
        Self { subj, to_add }
    }
}

#[derive(Clone, Copy, Debug)]
enum Rotation {
    U,
    R,
    D,
    L,
}

impl Rotation {
    fn decode(c: char) -> Self {
        match c {
            'U' => Self::U,
            'R' => Self::R,
            'D' => Self::D,
            'L' => Self::L,
            _ => panic!("Invalid rotation source `{}`", c),
        }
    }

    fn source_face_indices(self) -> [usize; 6] {
        match self {
            Self::U => [3, 0, 2, 5, 4, 1],
            Self::R => [4, 1, 0, 3, 5, 2],
            Self::D => [1, 5, 2, 0, 4, 3],
            Self::L => [2, 1, 5, 3, 0, 4],
        }
    }

    fn apply<T: Clone + Debug>(self, xs: [T; 6]) -> [T; 6] {
        self.source_face_indices()
            .into_iter()
            .map(|i| xs[i].clone())
            .collect::<Vec<_>>()
            .try_into()
            .unwrap()
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let isep = lines.iter().position(|s| s.is_empty()).unwrap();
    let mutations: Vec<Mutation> = lines[..isep].iter().map(|s| Mutation::decode(s)).collect();
    let roations: Vec<Rotation> = lines[isep + 1].chars().map(Rotation::decode).collect();
    let n: usize = 3;
    let mut absorptions = [1usize; 6];
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn four_times_up() {
        let xs = [0, 1, 2, 3, 4, 5];
        assert_ne!(Rotation::U.apply(xs), xs);

        assert_eq!(
            Rotation::U.apply(Rotation::U.apply(Rotation::U.apply(Rotation::U.apply(xs)))),
            xs
        );
    }

    #[test]
    fn four_times_right() {
        let xs = [0, 1, 2, 3, 4, 5];
        assert_ne!(Rotation::R.apply(xs), xs);

        assert_eq!(
            Rotation::R.apply(Rotation::R.apply(Rotation::R.apply(Rotation::R.apply(xs)))),
            xs
        );
    }

    #[test]
    fn four_times_down() {
        let xs = [0, 1, 2, 3, 4, 5];
        assert_ne!(Rotation::D.apply(xs), xs);

        assert_eq!(
            Rotation::D.apply(Rotation::D.apply(Rotation::D.apply(Rotation::D.apply(xs)))),
            xs
        );
    }

    #[test]
    fn four_times_left() {
        let xs = [0, 1, 2, 3, 4, 5];
        assert_ne!(Rotation::L.apply(xs), xs);

        assert_eq!(
            Rotation::L.apply(Rotation::L.apply(Rotation::L.apply(Rotation::L.apply(xs)))),
            xs
        );
    }
}
