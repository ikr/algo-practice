use ac_library::Dsu;
use std::{
    collections::HashSet,
    io::{BufRead, stdin},
};

use itertools::Itertools;

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

    fn is_in_bounds(self, grid_height: usize, grid_width: usize) -> bool {
        0 <= self.0
            && (self.0 as usize) < grid_height
            && 0 <= self.1
            && (self.1 as usize) < grid_width
    }

    fn flat_index(self, grid_width: usize) -> usize {
        let ro = self.0 as usize;
        let co = self.1 as usize;
        grid_width * ro + co
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

struct Grid {
    row_offsets: Vec<usize>,
    column_offsets: Vec<usize>,
}

impl Grid {
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

fn adjacency_list_from_edges(
    vertices_num: usize,
    edges: HashSet<(usize, usize)>,
) -> Vec<Vec<usize>> {
    edges
        .into_iter()
        .fold(vec![vec![]; vertices_num], |mut g, (u, v)| {
            g[u].push(v);
            g[v].push(u);
            g
        })
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
enum Color {
    None,
    A,
    B,
}

impl Color {
    fn opposite(self) -> Self {
        match self {
            Self::A => Self::B,
            Self::B => Self::A,
            Self::None => unreachable!(),
        }
    }
}

struct Coloring {
    g: Vec<Vec<usize>>,
    colors: Vec<Color>,
}

impl Coloring {
    fn new(g: Vec<Vec<usize>>) -> Self {
        let n = g.len();

        Self {
            g,
            colors: vec![Color::None; n],
        }
    }

    fn recur(&mut self, u: usize) {
        assert!(u < self.g.len());
        assert_ne!(self.colors[u], Color::None);

        for v in self.g[u].clone() {
            assert_ne!(self.colors[v], self.colors[u]);
            if self.colors[v] == Color::None {
                self.colors[v] = self.colors[u].opposite();
                self.recur(v);
            }
        }
    }

    fn apply(&mut self) {
        for u in 0..self.g.len() {
            if self.colors[u] == Color::None {
                self.colors[u] = Color::A;
                self.recur(u);
            }
        }
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

    let width = decode_line_int("width=", width_line);
    let height = decode_line_int("height=", height_line);
    let row_offsets = decode_line_flags("horizontal-offsets=", row_offsets_line);
    let column_offsets = decode_line_flags("vertical-offsets=", column_offsets_line);

    let g = Grid {
        row_offsets,
        column_offsets,
    };

    let mut dsu = Dsu::new(height * width);
    for ro in 0..height {
        for co in 0..width {
            let p = Crd::from_grid(ro, co);

            for dir in Dir::all() {
                let q = p + dir.delta();
                if q.is_in_bounds(height, width) && !g.has_border(p, dir) {
                    dsu.merge(p.flat_index(width), q.flat_index(width));
                }
            }
        }
    }

    let components = dsu.groups();
    let components_num = components.len();
    let mut component_index_by_flat_index: Vec<usize> = vec![usize::MAX; height * width];

    for (ci, fii) in components.into_iter().enumerate() {
        for fi in fii {
            component_index_by_flat_index[fi] = ci;
        }
    }
    eprintln!("{component_index_by_flat_index:?}");

    let mut component_adjacency_edges: HashSet<(usize, usize)> = HashSet::new();

    for ro in 0..height {
        for co in 0..width {
            let p = Crd::from_grid(ro, co);

            for dir in Dir::all() {
                let q = p + dir.delta();

                if q.is_in_bounds(height, width) && g.has_border(p, dir) {
                    let qi = q.flat_index(width);
                    let pi = p.flat_index(width);

                    if !dsu.same(pi, qi) {
                        let u = component_index_by_flat_index[pi];
                        let v = component_index_by_flat_index[qi];
                        component_adjacency_edges.insert((u.min(v), u.max(v)));
                    }
                }
            }
        }
    }
    eprintln!("{component_adjacency_edges:?}");

    let component_adjacency = adjacency_list_from_edges(components_num, component_adjacency_edges);
    eprintln!("{component_adjacency:?}");

    let mut coloring = Coloring::new(component_adjacency);
    coloring.apply();
    eprintln!("{:?}", coloring.colors);

    let isolated_tile_colors: Vec<Color> = (0..height)
        .cartesian_product(0..width)
        .filter_map(|(ro, co)| {
            Dir::all()
                .into_iter()
                .all(|dir| g.has_border(Crd::from_grid(ro, co), dir))
                .then(|| {
                    let p = Crd::from_grid(ro, co);
                    let fi = p.flat_index(width);
                    let ci = component_index_by_flat_index[fi];
                    coloring.colors[ci]
                })
        })
        .collect();

    let a = isolated_tile_colors
        .iter()
        .filter(|&&c| c == Color::A)
        .count();

    let b = isolated_tile_colors
        .iter()
        .filter(|&&c| c == Color::B)
        .count();

    assert_eq!(a + b, isolated_tile_colors.len());
    let result = a.max(b);
    println!("{result}");
}
