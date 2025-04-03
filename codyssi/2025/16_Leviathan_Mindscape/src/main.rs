use std::{
    fmt::Debug,
    io::{BufRead, stdin},
    iter::once,
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
            let x: usize = ab[1].parse().unwrap();
            match ab[0] {
                "ROW" => Self::Row(x - 1),
                "COL" => Self::Col(x - 1),
                _ => panic!("Invalid Subj source `{}`", s),
            }
        }
    }
}

#[derive(Clone, Copy, Debug)]
struct Mutation {
    subj: Subj,
    to_add: usize,
}

impl Mutation {
    fn decode(s: &str) -> Self {
        let ab: Vec<_> = s.split(" - VALUE ").collect();
        let subj = Subj::decode(ab[0]);
        let to_add: usize = ab[1].parse().unwrap();
        Self { subj, to_add }
    }
}

#[derive(Clone, Copy, Debug)]
enum FaceRotation {
    None,
    Clockwise,
    Counterclockwise,
    UpsideDown,
}

#[derive(Clone, Debug, PartialEq)]
struct Face {
    rows: Vec<Vec<usize>>,
}

impl Face {
    fn new(n: usize) -> Self {
        Self {
            rows: vec![vec![1; n]; n],
        }
    }

    fn size(&self) -> usize {
        self.rows.len()
    }

    fn transpose(&self) -> Self {
        let n = self.size();
        let mut rows: Vec<Vec<usize>> = vec![vec![0; n]; n];
        for (i, row) in self.rows.iter().enumerate() {
            for (j, &cell) in row.iter().enumerate() {
                rows[j][i] = cell;
            }
        }
        Self { rows }
    }

    fn dominant_row_sum(&self) -> usize {
        self.rows
            .iter()
            .map(|row| row.iter().sum::<usize>())
            .max()
            .unwrap()
    }

    fn dominant_sum(&self) -> usize {
        self.dominant_row_sum()
            .max(self.transpose().dominant_row_sum())
    }

    fn rotate_clockwise(&self) -> Self {
        let n = self.size();
        let mut rows: Vec<Vec<usize>> = vec![vec![0; n]; n];
        for (i, row) in self.rows.iter().enumerate() {
            for (j, &cell) in row.iter().enumerate() {
                rows[j][n - 1 - i] = cell;
            }
        }
        Self { rows }
    }

    fn rotate_counterclockwise(&self) -> Self {
        let n = self.size();
        let mut rows: Vec<Vec<usize>> = vec![vec![0; n]; n];
        for (i, row) in self.rows.iter().enumerate() {
            for (j, &cell) in row.iter().enumerate() {
                rows[n - 1 - j][i] = cell;
            }
        }
        Self { rows }
    }

    fn rotate_upside_down(&self) -> Self {
        let n = self.size();
        let mut rows: Vec<Vec<usize>> = vec![vec![0; n]; n];
        for (i, row) in self.rows.iter().enumerate() {
            for (j, &cell) in row.iter().enumerate() {
                rows[n - 1 - i][j] = cell;
            }
        }
        Self { rows }
    }

    fn apply(&self, mutation: Mutation) -> Self {
        match mutation.subj {
            Subj::Face => {
                let rows: Vec<Vec<usize>> = self
                    .rows
                    .iter()
                    .map(|row| row.iter().map(|&x| (x + mutation.to_add) % 100).collect())
                    .collect();
                Self { rows }
            }
            Subj::Row(i) => {
                let mut rows = self.rows.clone();
                for cell in rows[i].iter_mut() {
                    *cell += mutation.to_add;
                    *cell %= 100;
                }
                Self { rows }
            }
            Subj::Col(j) => {
                let mut rows = self.rows.clone();
                for row in rows.iter_mut() {
                    row[j] += mutation.to_add;
                    row[j] %= 100;
                }
                Self { rows }
            }
        }
    }
}

#[derive(Clone, Copy, Debug)]
enum Rotation {
    U,
    R,
    D,
    L,
    Noop,
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

    fn source_faces(self) -> [(usize, FaceRotation); 6] {
        match self {
            Self::U => [
                (3, FaceRotation::None),
                (0, FaceRotation::UpsideDown),
                (2, FaceRotation::Clockwise),
                (5, FaceRotation::None),
                (4, FaceRotation::Counterclockwise),
                (1, FaceRotation::UpsideDown),
            ],
            Self::R => [
                (4, FaceRotation::Clockwise),
                (1, FaceRotation::Counterclockwise),
                (0, FaceRotation::Clockwise),
                (3, FaceRotation::Clockwise),
                (5, FaceRotation::Clockwise),
                (2, FaceRotation::Clockwise),
            ],
            Self::D => [
                (1, FaceRotation::UpsideDown),
                (5, FaceRotation::UpsideDown),
                (2, FaceRotation::Counterclockwise),
                (0, FaceRotation::None),
                (4, FaceRotation::Clockwise),
                (3, FaceRotation::None),
            ],
            Self::L => [
                (2, FaceRotation::Counterclockwise),
                (1, FaceRotation::Clockwise),
                (5, FaceRotation::Counterclockwise),
                (3, FaceRotation::Counterclockwise),
                (0, FaceRotation::Counterclockwise),
                (4, FaceRotation::Counterclockwise),
            ],
            Self::Noop => (0..6)
                .map(|i| (i, FaceRotation::None))
                .collect::<Vec<_>>()
                .try_into()
                .unwrap(),
        }
    }

    fn apply(self, xs: &[Face]) -> Vec<Face> {
        assert_eq!(xs.len(), 6);
        self.source_faces()
            .into_iter()
            .map(|(i, fr)| {
                let ys = xs[i].clone();
                match fr {
                    FaceRotation::None => ys,
                    FaceRotation::Clockwise => ys.rotate_clockwise(),
                    FaceRotation::Counterclockwise => ys.rotate_counterclockwise(),
                    FaceRotation::UpsideDown => ys.rotate_upside_down(),
                }
            })
            .collect::<Vec<_>>()
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let isep = lines.iter().position(|s| s.is_empty()).unwrap();
    let mutations: Vec<Mutation> = lines[..isep].iter().map(|s| Mutation::decode(s)).collect();
    let rotations: Vec<Rotation> = lines[isep + 1]
        .chars()
        .map(Rotation::decode)
        .chain(once(Rotation::Noop))
        .collect();
    assert_eq!(mutations.len(), rotations.len());

    let n: usize = 80;
    let faces: Vec<Face> =
        mutations
            .into_iter()
            .zip(rotations)
            .fold(vec![Face::new(n); 6], |mut acc, (m, r)| {
                acc[0] = acc[0].apply(m);
                r.apply(&acc)
            });
    let result: u128 = faces
        .into_iter()
        .map(|f| f.dominant_sum() as u128)
        .product();
    println!("{}", result);
}

#[cfg(test)]
mod tests {
    use super::*;

    fn iota_face(n: usize) -> Face {
        let mut rows: Vec<Vec<usize>> = vec![vec![0; n]; n];
        for (i, row) in rows.iter_mut().enumerate() {
            for (j, cell) in row.iter_mut().enumerate() {
                *cell = i * n + j;
            }
        }
        Face { rows }
    }

    #[test]
    fn four_times_up() {
        let xs = vec![iota_face(4); 6];
        assert_ne!(Rotation::U.apply(&xs), xs);

        assert_eq!(
            Rotation::U.apply(&Rotation::U.apply(&Rotation::U.apply(&Rotation::U.apply(&xs)))),
            xs
        );
    }

    #[test]
    fn four_times_right() {
        let xs = vec![iota_face(4); 6];
        assert_ne!(Rotation::R.apply(&xs), xs);

        assert_eq!(
            Rotation::R.apply(&Rotation::R.apply(&Rotation::R.apply(&Rotation::R.apply(&xs)))),
            xs
        );
    }

    #[test]
    fn four_times_down() {
        let xs = vec![iota_face(4); 6];
        assert_ne!(Rotation::D.apply(&xs), xs);

        assert_eq!(
            Rotation::D.apply(&Rotation::D.apply(&Rotation::D.apply(&Rotation::D.apply(&xs)))),
            xs
        );
    }

    #[test]
    fn four_times_left() {
        let xs = vec![iota_face(4); 6];
        assert_ne!(Rotation::L.apply(&xs), xs);

        assert_eq!(
            Rotation::L.apply(&Rotation::L.apply(&Rotation::L.apply(&Rotation::L.apply(&xs)))),
            xs
        );
    }
}
