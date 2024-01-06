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

fn dbg_grid(grid: &Vec<Vec<char>>) {
    for row in grid.iter() {
        for c in row.iter() {
            eprint!("{}", c);
        }
        eprintln!();
    }
}

fn grid_with_units_added(
    mut grid: Vec<Vec<char>>,
    unit_locs: Vec<Location>,
    unit_symbol: char,
) -> Vec<Vec<char>> {
    for loc in unit_locs.iter() {
        grid[loc.row as usize][loc.column as usize] = unit_symbol;
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

#[derive(Eq, Hash, PartialEq)]
struct Location {
    row: usize,
    column: usize,
}

struct Unit {
    hit_points: u8,
    attack_power: u8,
}

struct Squad {
    units: HashMap<Location, Unit>,
    symbol: char,
}

impl Squad {
    fn in_grid(grid: &Vec<Vec<char>>, symbol: char) -> Squad {
        let mut units: HashMap<Location, Unit> = HashMap::new();
        for (row, row_vec) in grid.iter().enumerate() {
            for (column, c) in row_vec.iter().enumerate() {
                if *c == symbol {
                    units.insert(
                        Location { row, column },
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

fn main() {
    let grid = read_initial_grid_from_stdin();
    dbg_grid(&grid);
    dbg_grid(&depopulated_grid(&grid));
}
