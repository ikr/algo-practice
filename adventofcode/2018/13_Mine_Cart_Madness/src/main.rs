use std::collections::HashSet;
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

#[derive(Debug, Copy, Clone)]
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

#[derive(Debug, Copy, Clone, PartialEq, Eq, Hash)]
struct Loc {
    x: i32,
    y: i32,
}

#[derive(Debug, Copy, Clone)]
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
            phase: if c == '+' {
                cart.phase.next()
            } else {
                cart.phase
            },
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

fn carts_collision(carts: &Vec<Cart>) -> Option<Loc> {
    let mut seen: HashSet<Loc> = HashSet::new();
    for cart in carts.iter() {
        if seen.contains(&cart.loc) {
            return Some(cart.loc);
        }
        seen.insert(cart.loc);
    }
    None
}

fn move_one_by_one_skip_collisions(mine: &Mine, carts: &Vec<Cart>) -> Vec<Cart> {
    let mut result: Vec<Cart> = Vec::new();

    for cart in carts {
        result.push(mine.moved_cart(cart));
        if let Some(loc) = carts_collision(&result) {
            result = result.iter().filter(|c| c.loc != loc).cloned().collect();
        }
    }
    result
}

fn main() {
    let grid = read_grid_from_stdin();
    let mut carts = extract_carts(&grid);
    let mine = Mine { grid };

    loop {
        assert!(carts.len() > 1);
        carts.sort_by_key(|c| (c.loc.y, c.loc.x));

        carts = move_one_by_one_skip_collisions(&mine, &carts);
        if carts.len() == 1 {
            println!("{:?}", carts.get(0).unwrap());
            break;
        }
    }
}
