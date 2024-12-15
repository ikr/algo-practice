use std::{
    collections::HashSet,
    io::{self, BufRead},
};

use itertools::Itertools;

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i8, i8);

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

#[derive(Clone, Copy, Debug, Eq, PartialEq)]
enum Dir {
    N,
    E,
    S,
    W,
}

impl Dir {
    fn from_symbol(x: char) -> Dir {
        match x {
            '^' => Dir::N,
            '>' => Dir::E,
            'v' => Dir::S,
            '<' => Dir::W,
            _ => panic!("Invalid direction symbol: `{}`", x),
        }
    }

    fn delta(&self) -> Crd {
        match self {
            Dir::N => Crd(-1, 0),
            Dir::E => Crd(0, 1),
            Dir::S => Crd(1, 0),
            Dir::W => Crd(0, -1),
        }
    }
}

#[derive(Clone, Debug)]
struct Grid {
    robot: Crd,
    walls: HashSet<Crd>,
    boxes: HashSet<Crd>,
}

impl Grid {
    fn hit_box(&self, crd0: Crd, dir: Dir) -> Option<Crd> {
        let crd = crd0 + dir.delta();
        match dir {
            Dir::N | Dir::S => {
                if self.boxes.contains(&crd) {
                    Some(crd)
                } else if self.boxes.contains(&(crd + Dir::W.delta())) {
                    Some(crd + Dir::W.delta())
                } else {
                    None
                }
            }
            Dir::E => {
                if self.boxes.contains(&crd) {
                    Some(crd)
                } else {
                    None
                }
            }
            Dir::W => {
                if self.boxes.contains(&(crd + Dir::W.delta())) {
                    Some(crd + Dir::W.delta())
                } else {
                    None
                }
            }
        }
    }

    fn boxes_hit_clique(&self, crd0: Crd, dir: Dir) -> Vec<Crd> {
        assert!(self.boxes.contains(&crd0));
        let crd1 = crd0 + Dir::E.delta();
        let mut result = vec![crd0];

        for cause_crd in [crd0, crd1] {
            if let Some(crd) = self.hit_box(cause_crd, dir) {
                result.extend(self.boxes_hit_clique(crd, dir));
            }
        }

        result.into_iter().unique().collect()
    }

    fn boxes_hit_by_robot(&self, dir: Dir) -> Vec<Crd> {
        if let Some(crd) = self.hit_box(self.robot, dir) {
            self.boxes_hit_clique(crd, dir)
        } else {
            vec![]
        }
    }

    fn push_boxes_in_dir(&mut self, mut crd: Crd, dir: Dir) -> bool {
        assert!(self.boxes.contains(&crd));
        let mut to_shift: Vec<Crd> = vec![crd];
        while self.boxes.contains(&(crd + dir.delta())) {
            crd = crd + dir.delta();
            to_shift.push(crd);
        }

        let last_box = *to_shift.last().unwrap();
        if !self.walls.contains(&(last_box + dir.delta()))
            && !self.boxes.contains(&(last_box + dir.delta()))
        {
            for b in to_shift.iter() {
                self.boxes.remove(b);
            }
            for b in to_shift {
                self.boxes.insert(b + dir.delta());
            }
            true
        } else {
            false
        }
    }

    fn move_robot(&mut self, dir: Dir) {
        let new_robot = self.robot + dir.delta();
        if !self.walls.contains(&new_robot) {
            if self.boxes.contains(&new_robot) {
                if self.push_boxes_in_dir(new_robot, dir) {
                    self.robot = new_robot;
                }
            } else {
                self.robot = new_robot;
            }
        }
    }

    fn sum_of_box_gps_coordinates(&self) -> i32 {
        self.boxes
            .iter()
            .map(|Crd(i, j)| (*i as i32) * 100 + *j as i32)
            .sum()
    }

    fn eprintln(&self, h: usize, w: usize) {
        let mut grid = vec![vec!['.'; w]; h];
        for Crd(i, j) in self.walls.iter() {
            grid[*i as usize][*j as usize] = '#';
        }
        for Crd(i, j) in self.boxes.iter() {
            grid[*i as usize][*j as usize] = '[';
            grid[*i as usize][*j as usize + 1] = ']';
        }

        let Crd(ri, rj) = self.robot;
        grid[ri as usize][rj as usize] = '@';

        for row in grid {
            eprintln!("{}", row.iter().collect::<String>());
        }
    }
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().to_string())
        .collect();

    let isep = lines.iter().position(|x| x.is_empty()).unwrap();

    let grid0: Vec<Vec<char>> = lines[..isep]
        .iter()
        .map(|line| {
            line.chars().fold(vec![], |mut acc, x| {
                match x {
                    'O' => {
                        acc.push('[');
                        acc.push(']');
                    }
                    '@' => {
                        acc.push('@');
                        acc.push('.');
                    }
                    _ => {
                        acc.push(x);
                        acc.push(x);
                    }
                }
                acc
            })
        })
        .collect::<Vec<_>>();

    let program: String = lines[isep + 1..].join("");

    let (robot_initial, boxes_initial, walls): (Crd, Vec<Crd>, Vec<Crd>) = {
        let mut r = Crd(-1, -1);
        let mut bs = vec![];
        let mut ws = vec![];

        for (i, row) in grid0.iter().enumerate() {
            for (j, cell) in row.iter().enumerate() {
                let crd = Crd(i as i8, j as i8);
                match cell {
                    '@' => r = crd,
                    '[' => bs.push(crd),
                    '#' => ws.push(crd),
                    _ => {}
                }
            }
        }

        (r, bs, ws)
    };

    let grid = Grid {
        robot: robot_initial,
        walls: walls.into_iter().collect(),
        boxes: boxes_initial.into_iter().collect(),
    };

    let h = grid0.len();
    let w = grid0[0].len();
    grid.eprintln(h, w);
    println!();

    for symbol in program.chars() {
        //grid.move_robot(Dir::from_symbol(symbol));
        // grid.eprintln(h, w);
        // eprintln!();
    }

    println!("{}", grid.sum_of_box_gps_coordinates());
}
