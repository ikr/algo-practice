use itertools::Itertools;
use std::io::{BufRead, stdin};

fn decode_line_int(prefix: &str, line: String) -> usize {
    line.strip_prefix(prefix).unwrap().parse().unwrap()
}

fn decode_line_flags(prefix: &str, line: String) -> Vec<usize> {
    line.strip_prefix(prefix)
        .unwrap()
        .bytes()
        .map(|b| (b - b'0') as usize)
        .collect()
}

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i16, i16);

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

impl Crd {
    fn from_grid(row: usize, column: usize) -> Self {
        Self(row as i16, column as i16)
    }

    fn to_grid(self) -> (usize, usize) {
        (self.0 as usize, self.1 as usize)
    }
}

#[derive(Clone, Copy, Debug)]
enum Dir {
    N,
    E,
    S,
    W,
}

impl Dir {
    fn all() -> [Dir; 4] {
        [Self::N, Self::E, Self::S, Self::W]
    }

    fn delta(&self) -> Crd {
        match self {
            Dir::N => Crd(-1, 0),
            Dir::E => Crd(0, 1),
            Dir::S => Crd(1, 0),
            Dir::W => Crd(0, -1),
        }
    }
}

#[derive(Clone)]
struct PatternGrid {
    row_offsets: Vec<usize>,
    column_offsets: Vec<usize>,
}

impl PatternGrid {
    fn has_border(&self, crd: Crd, dir: Dir) -> bool {
        let (ro, co) = crd.to_grid();

        match dir {
            Dir::N => co % 2 == self.row_offsets[ro % self.row_offsets.len()],
            Dir::E => self.has_border(crd + Dir::E.delta(), Dir::W),
            Dir::S => self.has_border(crd + Dir::S.delta(), Dir::N),
            Dir::W => ro % 2 == self.column_offsets[co % self.column_offsets.len()],
        }
    }
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
enum Color {
    A,
    B,
}

impl Color {
    fn opposite(self) -> Self {
        match self {
            Self::A => Self::B,
            Self::B => Self::A,
        }
    }
}

struct Coloring {
    pg: PatternGrid,
    colors: Vec<Vec<Option<Color>>>,
}

impl Coloring {
    fn new(height: usize, width: usize, pg: PatternGrid) -> Self {
        Self {
            pg,
            colors: vec![vec![None; width]; height],
        }
    }

    fn height(&self) -> usize {
        self.colors.len()
    }

    fn width(&self) -> usize {
        self.colors[0].len()
    }

    fn at(&self, p: Crd) -> Option<Color> {
        let (ro, co) = p.to_grid();
        self.colors[ro][co]
    }

    fn set(&mut self, p: Crd, c: Color) {
        let (ro, co) = p.to_grid();
        self.colors[ro][co] = Some(c);
    }

    fn is_in_bounds(&self, p: Crd) -> bool {
        0 <= p.0 && (p.0 as usize) < self.height() && 0 <= p.1 && (p.1 as usize) < self.width()
    }

    fn recur(&mut self, u: Crd) {
        assert!(self.is_in_bounds(u));

        if let Some(uc) = self.at(u) {
            for dir in Dir::all() {
                let v = u + dir.delta();

                if self.is_in_bounds(v) && self.at(v).is_none() {
                    let c = if self.pg.has_border(u, dir) {
                        uc.opposite()
                    } else {
                        uc
                    };

                    self.set(v, c);
                    self.recur(v);
                }
            }
        } else {
            panic!("Recurring at a no-color {:?}", u);
        }
    }

    fn apply(&mut self) -> Vec<Vec<Color>> {
        for ro in 0..self.height() {
            for co in 0..self.width() {
                let p = Crd::from_grid(ro, co);

                if self.at(p).is_none() {
                    self.set(p, Color::A);
                    self.recur(p);
                }
            }
        }

        self.colors
            .iter()
            .map(|row| row.iter().map(|mbc| mbc.unwrap()).collect())
            .collect()
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();

    let [
        width_line,
        height_line,
        row_offsets_line,
        column_offsets_line,
    ] = lines.try_into().unwrap();

    let total_width = decode_line_int("width=", width_line);
    let total_height = decode_line_int("height=", height_line);
    let row_offsets = decode_line_flags("horizontal-offsets=", row_offsets_line);
    let column_offsets = decode_line_flags("vertical-offsets=", column_offsets_line);

    let height = row_offsets.len() * 2;
    let width = column_offsets.len() * 2;
    eprintln!("{height} x {width}");

    let pg = PatternGrid {
        row_offsets,
        column_offsets,
    };

    let pg_clone = pg.clone();
    let child_thread = std::thread::Builder::new()
        .stack_size(64 * 1024 * 1024)
        .spawn(move || {
            let mut coloring = Coloring::new(height, width, pg_clone);
            coloring.apply()
        })
        .unwrap();

    let colors: Vec<Vec<Color>> = child_thread.join().unwrap();

    let tile_loners: Vec<(usize, usize)> = {
        let isolated_tiles: Vec<(usize, usize, Color)> = (0..height)
            .cartesian_product(0..width)
            .filter(|&(ro, co)| {
                Dir::all()
                    .into_iter()
                    .all(|dir| pg.has_border(Crd::from_grid(ro, co), dir))
            })
            .map(|(ro, co)| (ro, co, colors[ro][co]))
            .collect();

        let (aa, bb): (Vec<_>, Vec<_>) = isolated_tiles
            .into_iter()
            .partition(|&(_, _, c)| c == Color::A);

        if aa.len() > bb.len() {
            aa
        } else if bb.len() > aa.len() {
            bb
        } else {
            unreachable!()
        }
        .into_iter()
        .map(|(ro, co, _)| (ro, co))
        .collect()
    };

    let n = total_height / height;
    let h = total_height % height;
    let m = total_width / width;
    let w = total_width % width;
    eprintln!("n:{n} h:{h} m:{m} w:{w}");

    let h_loners = tile_loners.iter().filter(|&&(ro, _)| ro < h).count();
    let w_loners = tile_loners.iter().filter(|&&(_, co)| co < w).count();

    let hw_loners = tile_loners
        .iter()
        .filter(|&&(ro, co)| ro < h && co < w)
        .count();

    eprintln!(
        "tile_loners:{} h_loners:{h_loners} w_loners:{w_loners} hw_loners:{hw_loners}",
        tile_loners.len()
    );

    let result = n * m * tile_loners.len() + n * w_loners + m * h_loners + hw_loners;
    println!("{result}");
}
