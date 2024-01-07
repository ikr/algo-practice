use std::collections::HashMap;

fn read_initial_grid_from_stdin() -> Vec<Vec<char>> {
    let mut result: Vec<Vec<char>> = Vec::new();
    loop {
        let mut line = String::new();
        let bytes_read = std::io::stdin().read_line(&mut line).unwrap();
        if bytes_read == 0 {
            break;
        }
        result.push(line.trim_end().chars().collect());
    }
    result
}

fn dbg_grid(grid: &Vec<Vec<char>>) -> () {
    for row in grid.iter() {
        for c in row.iter() {
            eprint!("{}", c);
        }
        eprintln!();
    }
}

fn grid_with_units_added(
    mut grid: Vec<Vec<char>>,
    unit_locs: Vec<Loc>,
    unit_symbol: char,
) -> Vec<Vec<char>> {
    for loc in unit_locs.iter() {
        grid[loc.ro as usize][loc.co as usize] = unit_symbol;
    }
    grid
}

fn depopulated_grid(grid: &Vec<Vec<char>>) -> Vec<Vec<char>> {
    let mut result: Vec<Vec<char>> = Vec::new();
    for row in grid.iter() {
        let mut new_row: Vec<char> = Vec::new();
        for c in row.iter() {
            match c {
                '#' | '.' => new_row.push(*c),
                _ => new_row.push('.'),
            }
        }
        result.push(new_row);
    }
    result
}

#[derive(Eq, Hash, PartialEq, Clone, Debug)]
struct Loc {
    ro: usize,
    co: usize,
}

struct Unit {
    hit_points: i32,
    attack_power: i32,
}

struct Squad {
    units: HashMap<Loc, Unit>,
    symbol: char,
}

impl Squad {
    fn in_grid(grid: &Vec<Vec<char>>, symbol: char) -> Squad {
        let mut units: HashMap<Loc, Unit> = HashMap::new();
        for (ro, row_vec) in grid.iter().enumerate() {
            for (co, cell) in row_vec.iter().enumerate() {
                if *cell == symbol {
                    units.insert(
                        Loc { ro, co },
                        Unit {
                            hit_points: 200,
                            attack_power: 3,
                        },
                    );
                }
            }
        }
        Squad { units, symbol }
    }
}

struct Dungeon {
    grid: Vec<Vec<char>>,
    squads: [Squad; 2],
}

impl Dungeon {
    fn play_round(&mut self) -> () {
        let mut q = self.all_unit_locations();
        q.sort_by_key(|loc| (-(loc.ro as i32), -(loc.co as i32)));
        eprintln!("q: {:?}", q);

        while !q.is_empty() {
            let loc = q.pop().unwrap();
            eprintln!("loc: {:?} squad idx: {}", loc, self.squad_index(&loc));

            // TODO
        }
    }

    fn all_unit_locations(&self) -> Vec<Loc> {
        let mut result: Vec<Loc> = Vec::new();
        for squad in self.squads.iter() {
            result.extend(squad.units.keys().cloned());
        }
        result
    }

    fn squad_index(&self, loc: &Loc) -> usize {
        for (i, squad) in self.squads.iter().enumerate() {
            if squad.units.contains_key(loc) {
                return i;
            }
        }
        panic!("No squad unit at location {:?}", loc);
    }

    fn adjacent(&self, loc: &Loc) -> Vec<Loc> {
        let mut result: Vec<Loc> = Vec::new();
        for (ro, co) in [
            (loc.ro - 1, loc.co),
            (loc.ro, loc.co + 1),
            (loc.ro + 1, loc.co),
            (loc.ro, loc.co - 1),
        ] {
            if self.cell_at(&Loc { ro, co }) == '.' {
                result.push(Loc { ro, co });
            }
        }
        result
    }

    fn cell_at(&self, loc: &Loc) -> char {
        for squad in self.squads.iter() {
            if squad.units.contains_key(loc) {
                return squad.symbol;
            }
        }
        self.grid[loc.ro][loc.co]
    }

    fn dbg(&self) -> () {
        let mut grid = self.grid.clone();
        for squad in self.squads.iter() {
            let locatoins: Vec<Loc> = squad.units.keys().cloned().collect();
            grid = grid_with_units_added(grid, locatoins, squad.symbol);
        }
        dbg_grid(&grid);
    }
}

fn main() {
    let grid = read_initial_grid_from_stdin();
    dbg_grid(&grid);
    eprintln!();
    dbg_grid(&depopulated_grid(&grid));
    eprintln!();

    let elves = Squad::in_grid(&grid, 'E');
    let goblins = Squad::in_grid(&grid, 'G');
    let mut dungeon = Dungeon {
        grid: depopulated_grid(&grid),
        squads: [elves, goblins],
    };

    dungeon.dbg();
    dungeon.play_round();
}
