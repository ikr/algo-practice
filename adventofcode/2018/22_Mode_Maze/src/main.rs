const M: usize = 20183;

#[derive(Clone, Copy)]
struct Vert(usize, usize);

struct Input {
    depth: usize,
    target: Vert,
}

fn in_a() -> Input {
    Input {
        depth: 510,
        target: Vert(10, 10),
    }
}

fn in_1() -> Input {
    Input {
        depth: 9171,
        target: Vert(7, 721),
    }
}

struct Cave {
    erosion: Vec<Vec<usize>>,
}

impl Cave {
    fn new(depth: usize, bottom_right: Vert) -> Self {
        let mut geo_idx = vec![vec![0; bottom_right.0 + 1]; bottom_right.1 + 1];
        let mut erosion = vec![vec![0; bottom_right.0 + 1]; bottom_right.1 + 1];

        for x in 0..=bottom_right.0 {
            geo_idx[0][x] = (x * 16807) % M;
            erosion[0][x] = (depth + geo_idx[0][x]) % M;
        }

        for y in 0..=bottom_right.1 {
            geo_idx[y][0] = (y * 48271) % M;
            erosion[y][0] = (depth + geo_idx[y][0]) % M;
        }

        for y in 1..=bottom_right.1 {
            for x in 1..=bottom_right.0 {
                geo_idx[y][x] = (erosion[y][x - 1] * erosion[y - 1][x]) % M;
                erosion[y][x] = (depth + geo_idx[y][x]) % M;
            }
        }

        geo_idx[bottom_right.1][bottom_right.0] = 0;
        erosion[bottom_right.1][bottom_right.0] = depth % M;
        Self { erosion }
    }

    fn risk(&self, v: Vert) -> usize {
        self.erosion[v.1][v.0] % 3
    }
}

fn main() {
    for input in &[in_a(), in_1()] {
        let c = Cave::new(input.depth, input.target);
        let mut risk: usize = 0;

        for y in 0..=input.target.1 {
            for x in 0..=input.target.0 {
                risk += c.risk(Vert(x, y));
            }
        }

        println!("{}", risk);
    }
}
