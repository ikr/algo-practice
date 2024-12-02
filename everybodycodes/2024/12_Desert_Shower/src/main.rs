use std::io::{self, BufRead};

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i32, i32);

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

struct Grid {
    rows: Vec<Vec<char>>,
}

impl Grid {
    fn in_bounds(&self, crd: Crd) -> bool {
        let Crd(ro, co) = crd;
        0 <= ro && ro < self.rows.len() as i32 && 0 <= co && co < self.rows[0].len() as i32
    }

    fn at(&self, crd: Crd) -> char {
        if self.in_bounds(crd) {
            let Crd(ro, co) = crd;
            self.rows[ro as usize][co as usize]
        } else {
            '.'
        }
    }

    fn is_ground(&self, crd: Crd) -> bool {
        crd.0 == (self.rows.len() - 1) as i32
    }

    fn cell_coordinates(&self, pred: fn(char) -> bool) -> Vec<Crd> {
        let mut result = vec![];
        for (i, row) in self.rows.iter().enumerate() {
            for (j, &cell) in row.iter().enumerate() {
                if pred(cell) {
                    result.push(Crd(i as i32, j as i32));
                }
            }
        }
        result
    }

    fn catapults(&self) -> Vec<Crd> {
        self.cell_coordinates(|c| c.is_ascii_uppercase() && c != 'T')
    }

    fn targets(&self) -> Vec<Crd> {
        self.cell_coordinates(|c| c == 'T')
    }

    fn trajectory_end(&self, catapult: Crd, shooting_power: i32) -> Crd {
        let mut cur: Crd = catapult;

        for _ in 0..shooting_power {
            cur = cur + Crd(-1, 1);
            if self.at(cur) == 'T' {
                return cur;
            }
        }

        for _ in 0..shooting_power {
            cur = cur + Crd(0, 1);
            if self.at(cur) == 'T' {
                return cur;
            }
        }

        loop {
            cur = cur + Crd(1, 1);
            if self.is_ground(cur) || self.at(cur) == 'T' {
                return cur;
            }
        }
    }

    fn shooting_power_to_hit(&self, catapult: Crd, target: Crd) -> Option<i32> {
        for sp in 1..64 {
            if self.trajectory_end(catapult, sp) == target {
                return Some(sp);
            }
        }
        None
    }
}

fn main() {
    let rows: Vec<Vec<char>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let grid = Grid { rows };
    eprintln!("{:?}", grid.catapults());
}
