use std::{
    collections::{HashMap, HashSet, VecDeque},
    io::{self, BufRead},
};

const HI: usize = 70;

fn parse_pair(s: &str) -> (i8, i8) {
    let parts = s.split(',').collect::<Vec<_>>();
    (parts[0].parse().unwrap(), parts[1].parse().unwrap())
}

fn main() {
    let ps: Vec<(i8, i8)> = io::stdin()
        .lock()
        .lines()
        .map(|line| parse_pair(&line.unwrap()))
        .collect();

    for lim in 1..=ps.len() {
        let obstacles: HashSet<(i8, i8)> = ps[0..lim].iter().cloned().collect();

        let mut distances: HashMap<(i8, i8), u16> = HashMap::new();
        distances.insert((0, 0), 0);
        let mut queue: VecDeque<(i8, i8)> = VecDeque::new();
        queue.push_back((0, 0));

        let adjacent = |(x, y): (i8, i8)| -> Vec<(i8, i8)> {
            let mut qs = vec![];
            if x > 0 && !obstacles.contains(&(x - 1, y)) {
                qs.push((x - 1, y));
            }
            if y > 0 && !obstacles.contains(&(x, y - 1)) {
                qs.push((x, y - 1));
            }
            if x < HI as i8 && !obstacles.contains(&(x + 1, y)) {
                qs.push((x + 1, y));
            }
            if y < HI as i8 && !obstacles.contains(&(x, y + 1)) {
                qs.push((x, y + 1));
            }
            qs
        };

        while let Some((x, y)) = queue.pop_front() {
            let d = distances[&(x, y)];
            for (nx, ny) in adjacent((x, y)) {
                if !distances.contains_key(&(nx, ny)) {
                    distances.insert((nx, ny), d + 1);
                    queue.push_back((nx, ny));
                }
            }
        }

        if !distances.contains_key(&(HI as i8, HI as i8)) {
            println!("{:?}", ps[lim - 1]);
            break;
        }
    }
}
