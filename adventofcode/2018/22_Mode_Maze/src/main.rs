const M: usize = 20183;
const LIM: usize = 1500;

#[derive(Clone, Copy)]
struct XY(usize, usize);

#[derive(Clone, Copy)]
enum Tile {
    Rocky,
    Wet,
    Narrow,
}

#[derive(Clone, Copy)]
enum Tool {
    Torch,
    Gear,
    None,
}

fn possible_tools(tile: Tile) -> Vec<Tool> {
    match tile {
        Tile::Rocky => vec![Tool::Torch, Tool::Gear],
        Tile::Wet => vec![Tool::Gear, Tool::None],
        Tile::Narrow => vec![Tool::Torch, Tool::None],
    }
}

struct Input {
    depth: usize,
    target: XY,
}

fn in_a() -> Input {
    Input {
        depth: 510,
        target: XY(10, 10),
    }
}

fn in_1() -> Input {
    Input {
        depth: 9171,
        target: XY(7, 721),
    }
}

struct Cave {
    erosion: Vec<Vec<usize>>,
}

impl Cave {
    fn new(depth: usize, target: XY) -> Self {
        let mut geo_idx = vec![vec![0; LIM]; LIM];
        let mut erosion = vec![vec![0; LIM]; LIM];

        for x in 0..LIM {
            geo_idx[0][x] = (x * 16807) % M;
            erosion[0][x] = (depth + geo_idx[0][x]) % M;
        }

        for y in 0..LIM {
            geo_idx[y][0] = (y * 48271) % M;
            erosion[y][0] = (depth + geo_idx[y][0]) % M;
        }

        for y in 1..LIM {
            for x in 1..LIM {
                geo_idx[y][x] = (erosion[y][x - 1] * erosion[y - 1][x]) % M;
                erosion[y][x] = (depth + geo_idx[y][x]) % M;
            }
        }

        geo_idx[target.1][target.0] = 0;
        erosion[target.1][target.0] = depth % M;
        Self { erosion }
    }

    fn risk(&self, xy: XY) -> usize {
        self.erosion[xy.1][xy.0] % 3
    }

    fn tile(&self, xy: XY) -> Tile {
        match self.risk(xy) {
            0 => Tile::Rocky,
            1 => Tile::Wet,
            2 => Tile::Narrow,
            _ => unreachable!(),
        }
    }
}

fn main() {
    for input in &[in_a(), in_1()] {
        let c = Cave::new(input.depth, input.target);
        let mut risk: usize = 0;

        for y in 0..=input.target.1 {
            for x in 0..=input.target.0 {
                risk += c.risk(XY(x, y));
            }
        }

        println!("{}", risk);
    }
}
