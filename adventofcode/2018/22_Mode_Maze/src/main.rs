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
    depth: usize,
    geo_idx: Vec<Vec<usize>>,
}

impl Cave {
    fn new(depth: usize, bottom_right: Vert) -> Self {
        let mut geo_idx = vec![vec![0; bottom_right.0 + 1]; bottom_right.1 + 1];

        for x in 0..=bottom_right.0 {
            geo_idx[0][x] = (x * 16807) % M;
        }

        for y in 0..=bottom_right.1 {
            geo_idx[y][0] = (y * 48271) % M;
        }

        for y in 1..=bottom_right.1 {
            for x in 1..=bottom_right.0 {
                geo_idx[y][x] = (geo_idx[y][x - 1] * geo_idx[y - 1][x]) % M;
            }
        }

        geo_idx[bottom_right.1][bottom_right.0] = 0;
        Self { depth, geo_idx }
    }

    fn erosion(&self, v: Vert) -> usize {
        assert!(v.1 < self.geo_idx.len() && v.0 < self.geo_idx[v.1].len());
        (self.depth + self.geo_idx[v.1][v.0]) % M
    }

    fn risk(&self, v: Vert) -> usize {
        self.erosion(v) % 3
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
