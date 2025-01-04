use std::io::{self, BufRead};

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

struct Grid {
    rows: Vec<Vec<u8>>,
}

impl Grid {
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

        let xs: Vec<u8> = src.into_iter().map(|Crd(i, j)| self.rows[i][j]).collect();

        for (x, Crd(i, j)) in xs.into_iter().zip(dst) {
            self.rows[i][j] = x;
        }
    }

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

    let mut g = Grid {
        rows: lines[2..].to_vec(),
    };

    for _ in 0..100 {
        for i in 1..g.height() - 1 {
            for j in 1..g.width() - 1 {
                let k = (i - 1) * (g.width() - 2) + j - 1;
                g.rotate_at(Crd(i, j), keys[k % keys.len()]);
            }
        }
    }

    g.eprintln();
}
