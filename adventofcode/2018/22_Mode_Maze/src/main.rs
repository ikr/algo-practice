const M: usize = 20183;

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

#[derive(Debug)]
struct Cave {
    geo_idx: Vec<Vec<usize>>,
}

impl Cave {
    fn new(depth: usize, bottom_right: Vert) -> Self {
        let mut geo_idx = vec![vec![0; bottom_right.1 + 1]; bottom_right.0 + 1];

        for x in 0..=bottom_right.0 {
            geo_idx[x][0] = (x * 16807) % M;
        }

        for y in 0..=bottom_right.1 {
            geo_idx[0][y] = (y * 48271) % M;
        }

        for y in 1..=bottom_right.1 {
            for x in 1..=bottom_right.0 {
                geo_idx[x][y] = (geo_idx[x - 1][y] * geo_idx[x][y - 1]) % M;
            }
        }

        geo_idx[bottom_right.0][bottom_right.1] = 0;
        Self { geo_idx }
    }
}

fn main() {
    let c_a = Cave::new(in_a().depth, in_a().target);
    eprintln!("{:?}", c_a.geo_idx);
}
