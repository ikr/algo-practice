use std::io::{self, BufRead};

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
struct Crd(i16, i16);

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

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

impl std::ops::Sub<Crd> for Crd {
    type Output = Crd;

    fn sub(self, o: Crd) -> Crd {
        Crd(self.0 - o.0, self.1 - o.1)
    }
}

#[derive(Clone, Debug)]
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

        let xs: Vec<T> = src
            .into_iter()
            .map(|Crd(i, j)| self.rows[i as usize][j as usize])
            .collect();

        for (x, Crd(i, j)) in xs.into_iter().zip(dst) {
            self.rows[i as usize][j as usize] = x;
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

    let mut g = Grid {
        rows: lines[2..].to_vec(),
    };

    let mut crd_rows: Vec<Vec<Crd>> = vec![vec![Crd(i16::MAX, i16::MAX); g.width()]; g.height()];
    for (i, row) in crd_rows.iter_mut().enumerate() {
        for (j, cell) in row.iter_mut().enumerate() {
            *cell = Crd(i as i16, j as i16);
        }
    }
    let mut cg = Grid { rows: crd_rows };

    let m = 1000;
    for _ in 0..m {
        for i in 1..cg.height() - 1 {
            for j in 1..cg.width() - 1 {
                let k = (i - 1) * (g.width() - 2) + j - 1;
                cg.rotate_at(Crd(i as i16, j as i16), keys[k % keys.len()]);
            }
        }
    }

    let mut routes: Vec<Vec<Crd>> = vec![vec![Crd(i16::MAX, i16::MAX); g.width()]; g.height()];
    for (i, row) in cg.rows.into_iter().enumerate() {
        for (j, src) in row.into_iter().enumerate() {
            let dst = Crd(i as i16, j as i16);
            let delta = dst - src;
            routes[src.0 as usize][src.1 as usize] = delta;
        }
    }

    for _ in 0..(ROUNDS / m) {
        let mut g_new = g.clone();

        for (i, row) in g.rows.iter().enumerate() {
            for (j, cell) in row.iter().enumerate() {
                let src = Crd(i as i16, j as i16);
                let dst = src + routes[i][j];
                g_new.rows[dst.0 as usize][dst.1 as usize] = *cell;
            }
        }

        g = g_new;
    }

    for _ in 0..(ROUNDS % m) {
        for i in 1..g.height() - 1 {
            for j in 1..g.width() - 1 {
                let k = (i - 1) * (g.width() - 2) + j - 1;
                g.rotate_at(Crd(i as i16, j as i16), keys[k % keys.len()]);
            }
        }
    }

    g.eprintln();
}
