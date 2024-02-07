use std::collections::{BTreeSet, HashMap};

const M: i32 = 20183;
const LIM: i32 = 1500;

#[derive(Clone, Copy)]
struct XY(i32, i32);

#[derive(Clone, Copy)]
enum Tile {
    Rocky,
    Wet,
    Narrow,
}

#[derive(Clone, Copy, PartialEq)]
enum Tool {
    Torch,
    Gear,
    None,
}

impl Tool {
    fn from_code(c: i32) -> Self {
        match c {
            0 => Self::Torch,
            1 => Self::Gear,
            2 => Self::None,
            _ => unreachable!(),
        }
    }

    fn code(&self) -> i32 {
        match self {
            Self::Torch => 0,
            Self::Gear => 1,
            Self::None => 2,
        }
    }
}

fn possible_tools(tile: Tile) -> Vec<Tool> {
    match tile {
        Tile::Rocky => vec![Tool::Torch, Tool::Gear],
        Tile::Wet => vec![Tool::Gear, Tool::None],
        Tile::Narrow => vec![Tool::Torch, Tool::None],
    }
}

#[derive(Clone, Copy)]
struct Vert {
    xy: XY,
    tool: Tool,
}

impl Vert {
    fn from_code(c: i32) -> Self {
        let tool = Tool::from_code(3i32 & c);
        let a = c >> 2;
        let x = a % LIM;
        let y = a / LIM;
        Vert { xy: XY(x, y), tool }
    }

    fn code(&self) -> i32 {
        let a = (self.xy.1 * LIM + self.xy.0) as i32;
        (a << 2) | self.tool.code()
    }
}

struct Edge {
    vcode: i32,
    weight: i32,
}

struct Input {
    depth: i32,
    target_xy: XY,
}

fn in_a() -> Input {
    Input {
        depth: 510,
        target_xy: XY(10, 10),
    }
}

fn in_1() -> Input {
    Input {
        depth: 9171,
        target_xy: XY(7, 721),
    }
}

struct Cave {
    erosion: Vec<Vec<i32>>,
}

impl Cave {
    fn new(depth: i32, target_xy: XY) -> Self {
        let mut geo_idx = vec![vec![0; LIM as usize]; LIM as usize];
        let mut erosion = vec![vec![0; LIM as usize]; LIM as usize];

        for x in 0..LIM {
            geo_idx[0][x as usize] = (x * 16807) % M;
            erosion[0][x as usize] = (depth + geo_idx[0][x as usize]) % M;
        }

        for y in 0..LIM {
            geo_idx[y as usize][0] = (y * 48271) % M;
            erosion[y as usize][0] = (depth + geo_idx[y as usize][0]) % M;
        }

        for y in 1..LIM {
            for x in 1..LIM {
                geo_idx[y as usize][x as usize] =
                    (erosion[y as usize][x as usize - 1] * erosion[y as usize - 1][x as usize]) % M;
                erosion[y as usize][x as usize] = (depth + geo_idx[y as usize][x as usize]) % M;
            }
        }

        geo_idx[target_xy.1 as usize][target_xy.0 as usize] = 0;
        erosion[target_xy.1 as usize][target_xy.0 as usize] = depth % M;
        Self { erosion }
    }

    fn risk(&self, xy: XY) -> i32 {
        self.erosion[xy.1 as usize][xy.0 as usize] % 3
    }

    fn tile(&self, xy: XY) -> Tile {
        match self.risk(xy) {
            0 => Tile::Rocky,
            1 => Tile::Wet,
            2 => Tile::Narrow,
            _ => unreachable!(),
        }
    }

    fn incident(&self, u: Vert) -> Vec<Edge> {
        let pts = possible_tools(self.tile(u.xy));
        assert!(pts.contains(&u.tool));

        let mut result: Vec<Edge> = Vec::new();
        for (x, y) in &[
            (u.xy.0, u.xy.1 - 1),
            (u.xy.0 + 1, u.xy.1),
            (u.xy.0, u.xy.1 + 1),
            (u.xy.0 - 1, u.xy.1),
        ] {
            if *x < 0 || *y < 0 || *x >= LIM || *y >= LIM {
                continue;
            }

            let tile = self.tile(XY(*x, *y));
            if possible_tools(tile).contains(&u.tool) {
                result.push(Edge {
                    vcode: Vert {
                        xy: XY(*x, *y),
                        tool: u.tool,
                    }
                    .code(),
                    weight: 1,
                })
            }
        }

        for tool in pts {
            if tool == u.tool {
                continue;
            }
            result.push(Edge {
                vcode: Vert { xy: u.xy, tool }.code(),
                weight: 7,
            })
        }
        result
    }

    fn dijkstra(&self, source: Vert, target: Vert) -> i32 {
        let mut dist: HashMap<i32, i32> = HashMap::new();
        dist.insert(source.code(), 0);

        let mut q: BTreeSet<(i32, i32)> = BTreeSet::new();
        q.insert((0, source.code()));

        while let Some((_, u)) = q.pop_first() {
            for e in self.incident(Vert::from_code(u)) {
                let alt = dist[&u] + e.weight;
                if !dist.contains_key(&e.vcode) || alt < dist[&e.vcode] {
                    dist.insert(e.vcode, alt);
                    q.insert((alt, e.vcode));
                }
            }
        }

        dist[&target.code()]
    }
}

fn main() {
    for input in &[in_a(), in_1()] {
        let c = Cave::new(input.depth, input.target_xy);
        let mut risk: i32 = 0;

        for y in 0..=input.target_xy.1 {
            for x in 0..=input.target_xy.0 {
                risk += c.risk(XY(x, y));
            }
        }

        println!("Part 1 answer: {}", risk);
        println!(
            "Part 2 answer: {}",
            c.dijkstra(
                Vert {
                    xy: XY(0, 0),
                    tool: Tool::Torch
                },
                Vert {
                    xy: input.target_xy,
                    tool: Tool::Torch
                }
            )
        );
    }
}
