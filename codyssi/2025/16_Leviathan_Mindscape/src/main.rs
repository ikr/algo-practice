use std::{
    fmt::Debug,
    io::{BufRead, stdin},
    iter::once,
};

fn not_mod_100(x: usize) -> usize {
    let result = x % 100;
    if result == 0 { 100 } else { result }
}

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

impl FaceRotation {
    fn inverse(self) -> Self {
        match self {
            Self::None => Self::None,
            Self::Clockwise => Self::Counterclockwise,
            Self::Counterclockwise => Self::Clockwise,
            Self::UpsideDown => Self::UpsideDown,
        }
    }
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
        let mut rows: Vec<Vec<usize>> = self.rows.clone();
        for i in 0..n {
            for j in i + 1..n {
                (rows[i][j], rows[j][i]) = (rows[j][i], rows[i][j]);
            }
        }
        Self { rows }
    }

    fn revert_rows(&self) -> Self {
        let rows: Vec<Vec<usize>> = self
            .rows
            .iter()
            .map(|row| row.iter().cloned().rev().collect())
            .collect();
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
        self.transpose().revert_rows()
    }

    fn rotate_counterclockwise(&self) -> Self {
        self.revert_rows().transpose()
    }

    fn apply_rotation(&self, rotation: FaceRotation) -> Self {
        match rotation {
            FaceRotation::None => self.clone(),
            FaceRotation::Clockwise => self.rotate_clockwise(),
            FaceRotation::Counterclockwise => self.rotate_counterclockwise(),
            FaceRotation::UpsideDown => self.rotate_clockwise().rotate_clockwise(),
        }
    }

    fn apply_mutation(&self, mutation: Mutation) -> Self {
        match mutation.subj {
            Subj::Face => {
                let rows: Vec<Vec<usize>> = self
                    .rows
                    .iter()
                    .map(|row| {
                        row.iter()
                            .map(|&x| not_mod_100(x + mutation.to_add))
                            .collect()
                    })
                    .collect();
                Self { rows }
            }
            Subj::Row(i) => {
                let mut rows = self.rows.clone();
                for cell in rows[i].iter_mut() {
                    *cell += mutation.to_add;
                    *cell = not_mod_100(*cell);
                }
                Self { rows }
            }
            Subj::Col(j) => {
                let mut rows = self.rows.clone();
                for row in rows.iter_mut() {
                    row[j] += mutation.to_add;
                    row[j] = not_mod_100(row[j]);
                }
                Self { rows }
            }
        }
    }
}

#[derive(Clone, Copy, Debug, PartialEq)]
struct Orientation(i8, i8, i8);

impl Orientation {
    fn new() -> Self {
        Self(1, 2, 3)
    }

    fn front_face_and_its_rotation(self) -> (usize, FaceRotation) {
        let Self(x, y, z) = self;
        match (x, y, z) {
            (1, 2, 3) => (0, FaceRotation::None),
            _ => panic!("Unexpected {:?}", self),
        }
    }
}

#[derive(Clone, Copy, Debug)]
enum Rotation {
    U,
    R,
    D,
    L,
    None,
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

    fn apply(self, o: Orientation) -> Orientation {
        let Orientation(x, y, z) = o;
        match self {
            Rotation::U => Orientation(z, y, -x),
            Rotation::R => Orientation(x, -z, y),
            Rotation::D => Orientation(-z, y, x),
            Rotation::L => Orientation(x, z, -y),
            Rotation::None => o,
        }
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let isep = lines.iter().position(|s| s.is_empty()).unwrap();
    let mutations: Vec<Mutation> = lines[..isep].iter().map(|s| Mutation::decode(s)).collect();
    let rotations: Vec<Rotation> = lines[isep + 1]
        .chars()
        .map(Rotation::decode)
        .chain(once(Rotation::None))
        .collect();
    assert_eq!(mutations.len(), rotations.len());

    let n: usize = 3;
    let mut faces = vec![Face::new(n); 6];
    let mut o = Orientation::new();

    for (m, r) in mutations.into_iter().zip(rotations) {
        let (iface, face_rotation) = o.front_face_and_its_rotation();

        faces[iface] = faces[iface]
            .apply_rotation(face_rotation)
            .apply_mutation(m)
            .apply_rotation(face_rotation.inverse());

        o = r.apply(o);
    }

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
    fn four_rotations_are_identical() {
        let o = Orientation::new();
        for r in [Rotation::U, Rotation::R, Rotation::D, Rotation::L] {
            assert_ne!(r.apply(o), o);
            assert_eq!(r.apply(r.apply(r.apply(r.apply(o)))), o);
        }
    }

    #[test]
    fn lr_rotation_is_id() {
        let o = Orientation::new();
        assert_eq!(Rotation::R.apply(Rotation::L.apply(o)), o);
    }

    #[test]
    fn ud_rotation_is_id() {
        let o = Orientation::new();
        assert_eq!(Rotation::U.apply(Rotation::D.apply(o)), o);
    }

    #[test]
    fn ll_rr_rotation_equivalence() {
        let o = Orientation::new();
        let a = Rotation::L.apply(Rotation::L.apply(o));
        let b = Rotation::R.apply(Rotation::R.apply(o));
        assert_eq!(a, b);
    }

    #[test]
    fn uu_dd_rotation_equivalence() {
        let o = Orientation::new();
        let a = Rotation::U.apply(Rotation::U.apply(o));
        let b = Rotation::D.apply(Rotation::D.apply(o));
        assert_eq!(a, b);
    }

    #[test]
    fn face_double_transpose_is_identical() {
        let f = iota_face(4);
        assert_eq!(f.transpose().transpose(), f);
    }

    #[test]
    fn face_ccw_cancels_cw() {
        let f = iota_face(4);
        assert_eq!(f.rotate_clockwise().rotate_counterclockwise(), f);
    }

    #[test]
    fn face_2cw_2ccw() {
        let f = iota_face(4);
        assert_eq!(
            f.rotate_clockwise().rotate_clockwise(),
            f.rotate_counterclockwise().rotate_counterclockwise()
        );
    }

    #[test]
    fn face_4cw_is_id() {
        let f = iota_face(5);
        assert_eq!(
            f.rotate_clockwise()
                .rotate_clockwise()
                .rotate_clockwise()
                .rotate_clockwise(),
            f
        );
    }

    #[test]
    fn face_4ccw_is_id() {
        let f = iota_face(5);
        assert_eq!(
            f.rotate_counterclockwise()
                .rotate_counterclockwise()
                .rotate_counterclockwise()
                .rotate_counterclockwise(),
            f
        );
    }

    #[test]
    fn transposition_changing_all_outside_of_main_diagonal() {
        let fa = iota_face(9);
        let fb = fa.transpose();

        let a = fa.rows;
        let b = fb.rows;

        for i in 0..6 {
            assert_eq!(a[i][i], b[i][i]);
            for j in 0..6 {
                if i != j {
                    assert_ne!(a[i][j], b[i][j]);
                }
            }
        }
    }
}
