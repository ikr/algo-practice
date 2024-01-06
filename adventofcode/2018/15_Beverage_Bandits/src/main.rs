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

fn main() {
    let grid = read_initial_grid_from_stdin();
    dbg_grid(&grid);
    dbg_grid(&depopulated_grid(&grid));
}
