use std::cell;
use std::io::{self, BufRead};
use std::ops::Add;

#[derive(Debug, Clone, Copy)]
enum Dir {
    N,
    E,
    S,
    W,
}

#[derive(Debug, Clone, Copy)]
struct Roco(i32, i32);

impl Add<Roco> for Roco {
    type Output = Roco;

    fn add(self, o: Roco) -> Roco {
        Roco(self.0 + o.0, self.1 + o.1)
    }
}

fn dir_delta(dir: Dir) -> Roco {
    match dir {
        Dir::N => Roco(-1, 0),
        Dir::E => Roco(0, 1),
        Dir::S => Roco(1, 0),
        Dir::W => Roco(-1, 0),
    }
}

fn index_of_entrance(top_row: &[char]) -> usize {
    top_row.iter().position(|&x| x == '|').unwrap()
}

fn dimensions(grid: &[Vec<char>]) -> Roco {
    Roco(grid.len() as i32, grid[0].len() as i32)
}

fn trace(grid: &[Vec<char>]) -> String {
    let mut result = String::new();
    let mut roco = Roco(0, index_of_entrance(&grid[0]) as i32);
    let mut dir = Dir::S;

    loop {
        while grid[roco.0 as usize][roco.1 as usize] != ' '
            && grid[roco.0 as usize][roco.1 as usize] != '+'
        {
            roco = roco + dir_delta(dir);
        }

        if grid[roco.0 as usize][roco.1 as usize] == '+' {
            break;
        }
    }

    result
}

fn main() {
    let grid: Vec<Vec<char>> = io::stdin()
        .lock()
        .lines()
        .map(|x| x.unwrap().chars().collect())
        .collect();

    eprintln!("{:?}", grid);
    eprintln!("Dimensions: {:?}", dimensions(&grid));
    eprintln!("Entrance at column {}", index_of_entrance(&grid[0]));

    println!("{}", trace(&grid));
}
