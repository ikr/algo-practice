use std::io::{self, BufRead};

#[derive(Debug, Copy, Clone)]
enum Dir {
    N,
    E,
    S,
    W,
}

impl Dir {
    fn decode(c: char) -> Dir {
        match c {
            '^' => Dir::N,
            '>' => Dir::E,
            'v' => Dir::S,
            '<' => Dir::W,
            _ => panic!("Invalid direction char `{}`", c),
        }
    }
}

#[derive(Debug)]
enum Phase {
    Left,
    Straight,
    Right,
}

impl Phase {
    fn next(&self) -> Phase {
        match self {
            Phase::Left => Phase::Straight,
            Phase::Straight => Phase::Right,
            Phase::Right => Phase::Left,
        }
    }
}

#[derive(Debug)]
struct Loc {
    x: i32,
    y: i32,
}

#[derive(Debug)]
struct Cart {
    loc: Loc,
    dir: Dir,
    phase: Phase,
}

impl Cart {
    fn next_loc(&self) -> Loc {
        match self.dir {
            Dir::N => Loc {
                x: self.loc.x,
                y: self.loc.y - 1,
            },
            Dir::E => Loc {
                x: self.loc.x + 1,
                y: self.loc.y,
            },
            Dir::S => Loc {
                x: self.loc.x,
                y: self.loc.y + 1,
            },
            Dir::W => Loc {
                x: self.loc.x - 1,
                y: self.loc.y,
            },
        }
    }
}

struct Mine {
    grid: Vec<Vec<char>>,
}

impl Mine {
    fn cell(&self, loc: &Loc) -> char {
        self.grid[loc.y as usize][loc.x as usize]
    }

    fn moved_cart(&self, cart: &Cart) -> Cart {
        let loc_ = cart.next_loc();
        let c = self.cell(&loc_);

        let dir_ = match c {
            '/' => match cart.dir {
                Dir::N => Dir::E,
                Dir::E => Dir::N,
                Dir::S => Dir::W,
                Dir::W => Dir::S,
            },
            '\\' => match cart.dir {
                Dir::N => Dir::W,
                Dir::E => Dir::S,
                Dir::S => Dir::E,
                Dir::W => Dir::N,
            },
            '+' => match cart.phase {
                Phase::Left => match cart.dir {
                    Dir::N => Dir::W,
                    Dir::E => Dir::N,
                    Dir::S => Dir::E,
                    Dir::W => Dir::S,
                },
                Phase::Straight => cart.dir,
                Phase::Right => match cart.dir {
                    Dir::N => Dir::E,
                    Dir::E => Dir::S,
                    Dir::S => Dir::W,
                    Dir::W => Dir::N,
                },
            },
            _ => cart.dir,
        };
        Cart {
            loc: loc_,
            dir: dir_,
            phase: cart.phase.next(),
        }
    }
}

fn read_grid_from_stdin() -> Vec<Vec<char>> {
    io::stdin()
        .lock()
        .lines()
        .map(|l| l.unwrap().chars().collect())
        .collect()
}

fn extract_carts(grid: &Vec<Vec<char>>) -> Vec<Cart> {
    let mut result: Vec<Cart> = Vec::new();
    for (y, row) in grid.iter().enumerate() {
        for (x, c) in row.iter().enumerate() {
            match c {
                '^' | '>' | 'v' | '<' => result.push(Cart {
                    loc: Loc {
                        x: x as i32,
                        y: y as i32,
                    },
                    dir: Dir::decode(*c),
                    phase: Phase::Left,
                }),
                _ => (),
            }
        }
    }
    result
}

fn main() {
    println!("{:?}", extract_carts(&read_grid_from_stdin()));
}
