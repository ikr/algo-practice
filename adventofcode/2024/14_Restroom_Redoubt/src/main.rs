use ac_library::Dsu;
use crossterm::{
    cursor, execute,
    style::Print,
    terminal::{self, ClearType},
};
use itertools::Itertools;
use regex::Regex;
use std::io::{self, BufRead};

const H: i32 = 103;
const W: i32 = 101;

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i32, i32);

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

struct Robot {
    position: Crd,
    velocity: Crd,
}

impl Robot {
    fn new(position: Crd, velocity: Crd) -> Robot {
        Robot { position, velocity }
    }

    fn tick(&self) -> Robot {
        let Crd(x0, y0) = self.position + self.velocity;
        let x = (x0 + 10 * W) % W;
        let y = (y0 + 10 * H) % H;

        Robot {
            position: Crd(x, y),
            velocity: self.velocity,
        }
    }
}

fn parse_point_and_velocity(s: &str) -> (Crd, Crd) {
    let re = Regex::new(r"^p=(\d+),(\d+) v=(-?\d+),(-?\d+)$").unwrap();
    let caps = re.captures(s).unwrap();
    (
        Crd(caps[1].parse().unwrap(), caps[2].parse().unwrap()),
        Crd(caps[3].parse().unwrap(), caps[4].parse().unwrap()),
    )
}

fn connected_components_num(ps: &[Crd]) -> usize {
    let n = ps.len();
    let mut dsu = Dsu::new(n);
    for pq in ps.iter().enumerate().combinations(2) {
        let (i, Crd(px, py)) = pq[0];
        let (j, Crd(qx, qy)) = pq[1];
        if px.abs_diff(*qx).max(py.abs_diff(*qy)) == 1 {
            dsu.merge(i, j);
        }
    }
    dsu.groups().len()
}

fn sleep(millis: u64) {
    std::thread::sleep(std::time::Duration::from_millis(millis));
}

fn display_robots_on_a_grid(t: u32, robots: &Vec<Robot>) {
    let mut grid = vec![vec!['.'; W as usize]; H as usize];
    for robot in robots.iter() {
        let Crd(x, y) = robot.position;
        grid[y as usize][x as usize] = '#';
    }

    let cs = connected_components_num(&robots.iter().map(|r| r.position).collect::<Vec<_>>());

    execute!(
        io::stdout(),
        terminal::Clear(ClearType::All),
        cursor::Hide,
        cursor::MoveTo(1, 1),
        Print(t.to_string() + " cs:" + cs.to_string().as_str()),
        Print("\n")
    )
    .unwrap();

    for row in grid.iter() {
        execute!(
            io::stdout(),
            Print(row.iter().collect::<String>()),
            Print("\n")
        )
        .unwrap();
    }

    execute!(io::stdout(), Print("\n")).unwrap();
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().to_string())
        .collect();

    let points_and_velocities: Vec<(Crd, Crd)> =
        lines.iter().map(|s| parse_point_and_velocity(s)).collect();

    let mut robots: Vec<Robot> = points_and_velocities
        .iter()
        .map(|(p, v)| Robot::new(*p, *v))
        .collect();

    let hi = 1_000_000;
    let mut locs = usize::MAX;
    for t in 1..=hi {
        for robot in robots.iter_mut() {
            *robot = robot.tick();
        }
        let cs = connected_components_num(&robots.iter().map(|r| r.position).collect::<Vec<_>>());
        if cs < locs {
            display_robots_on_a_grid(t, &robots);
            locs = cs;
        }
    }
}
