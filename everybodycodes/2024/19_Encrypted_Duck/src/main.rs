use std::io::{self, BufRead};

use num_integer::lcm;

const ROUNDS: usize = 1_048_576_000;

#[derive(Clone, Copy, Debug)]
enum Dir {
    L,
    R,
}

impl Dir {
    fn from(c: u8) -> Dir {
        match c {
            b'L' => Dir::L,
            b'R' => Dir::R,
            _ => panic!("Got {}", c),
        }
    }
}

#[derive(Clone, Copy, Debug)]
struct Crd(usize, usize);

impl Crd {
    fn neighborhood(&self) -> Vec<Crd> {
        let Crd(i, j) = *self;
        assert_ne!(i, 0);
        assert_ne!(j, 0);
        vec![
            Crd(i - 1, j - 1),
            Crd(i - 1, j),
            Crd(i - 1, j + 1),
            Crd(i, j + 1),
            Crd(i + 1, j + 1),
            Crd(i + 1, j),
            Crd(i + 1, j - 1),
            Crd(i, j - 1),
        ]
    }
}

struct Grid<T> {
    rows: Vec<Vec<T>>,
}

impl<T> Grid<T>
where
    T: Copy,
{
    fn height(&self) -> usize {
        self.rows.len()
    }

    fn width(&self) -> usize {
        assert!(!self.rows.is_empty());
        self.rows[0].len()
    }

    fn rotate_at(&mut self, point: Crd, dir: Dir) {
        let src = point.neighborhood();
        let mut dst = src.clone();
        match dir {
            Dir::L => dst.rotate_right(1),
            Dir::R => dst.rotate_left(1),
        }

        let xs: Vec<T> = src.into_iter().map(|Crd(i, j)| self.rows[i][j]).collect();

        for (x, Crd(i, j)) in xs.into_iter().zip(dst) {
            self.rows[i][j] = x;
        }
    }
}

impl Grid<u8> {
    fn eprintln(&self) {
        for row in self.rows.iter() {
            eprintln!("{}", String::from_utf8(row.to_vec()).unwrap());
        }
    }
}

fn main() {
    let lines: Vec<Vec<u8>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().bytes().collect())
        .collect();

    let keys: Vec<Dir> = lines[0].iter().map(|x| Dir::from(*x)).collect();

    let g = Grid {
        rows: lines[2..].to_vec(),
    };

    let mut crd_rows: Vec<Vec<Crd>> = vec![vec![Crd(0, 0); g.width()]; g.height()];
    for i in 0..g.height() {
        for j in 0..g.width() {
            crd_rows[i][j] = Crd(i, j);
        }
    }
    let mut cg = Grid { rows: crd_rows };

    let rotation_points_num = (g.height() - 2) * (g.width() - 2);
    let m = lcm(rotation_points_num, keys.len());
    let mut k: usize = 0;
    'outer: loop {
        for i in 1..cg.height() - 1 {
            for j in 1..cg.width() - 1 {
                cg.rotate_at(Crd(i, j), keys[k % keys.len()]);
                k += 1;
                if k == m {
                    break 'outer;
                }
            }
        }
    }

    // for _ in 0..1_048_576_000 {
    //     for i in 1..g.height() - 1 {
    //         for j in 1..g.width() - 1 {
    //             let k = (i - 1) * (g.width() - 2) + j - 1;
    //             g.rotate_at(Crd(i, j), keys[k % keys.len()]);
    //         }
    //     }
    // }

    // g.eprintln();
}
