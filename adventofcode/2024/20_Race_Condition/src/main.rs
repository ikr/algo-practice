use std::{
    collections::{HashMap, VecDeque},
    io::{self, BufRead},
};

const INF: usize = 10_000_000;

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(usize, usize);

impl Crd {
    fn north(&self) -> Option<Crd> {
        if self.0 != 0 {
            Some(Crd(self.0, self.1))
        } else {
            None
        }
    }

    fn east(&self, w: usize) -> Option<Crd> {
        if self.1 < w - 1 {
            Some(Crd(self.0, self.1 + 1))
        } else {
            None
        }
    }

    fn south(&self, h: usize) -> Option<Crd> {
        if self.0 < h - 1 {
            Some(Crd(self.0 + 1, self.1))
        } else {
            None
        }
    }

    fn west(&self) -> Option<Crd> {
        if self.1 != 0 {
            Some(Crd(self.0, self.1 - 1))
        } else {
            None
        }
    }

    fn adjacent(&self, h: usize, w: usize) -> Vec<Crd> {
        [self.north(), self.east(w), self.south(h), self.west()]
            .iter()
            .filter_map(|x| *x)
            .collect()
    }
}

fn bfs(grid: &[Vec<char>], start: Crd) -> (Vec<Vec<usize>>, Vec<Vec<Option<Crd>>>) {
    let h = grid.len();
    let w = grid[0].len();

    let mut distance: Vec<Vec<usize>> = vec![vec![INF; w]; h];
    distance[start.0][start.1] = 0;

    let mut pre: Vec<Vec<Option<Crd>>> = vec![vec![None; w]; h];
    let mut queue: VecDeque<Crd> = VecDeque::from([start]);

    let adjacent = |p: Crd| -> Vec<Crd> {
        p.adjacent(h, w)
            .into_iter()
            .filter_map(|q| if grid[q.0][q.1] != '#' { Some(q) } else { None })
            .collect()
    };

    while let Some(p) = queue.pop_front() {
        for q in adjacent(p) {
            if distance[q.0][q.1] == INF {
                distance[q.0][q.1] = distance[p.0][p.1] + 1;
                pre[q.0][q.1] = Some(p);
                queue.push_back(q);
            }
        }
    }

    (distance, pre)
}

fn recover_path(pre: &Vec<Vec<Option<Crd>>>, end: Crd) -> Vec<Crd> {
    let mut path = vec![];
    let mut p = end;

    loop {
        path.push(p);
        if let Some(pp) = pre[p.0][p.1] {
            p = pp;
        } else {
            break;
        }
    }

    path.reverse();
    path
}

fn optimal_distance_in_the_walls_under_20(grid: &[Vec<char>], start: Crd, end: Crd) -> usize {
    for p in [start, end] {
        assert_ne!(grid[p.0][p.1], '#');
    }

    if start == end {
        return 0;
    }

    let h = grid.len();
    let w = grid[0].len();

    let in_bounds =
        |c: Crd| -> bool { 0 <= c.0 && c.0 < grid.len() && 0 <= c.1 && c.1 < grid[0].len() };

    let adjacent = |p: Crd| -> Vec<Crd> {
        p.adjacent(h, w)
            .into_iter()
            .filter_map(|q| if in_bounds(q) { Some(q) } else { None })
            .collect()
    };

    let mut distance: HashMap<Crd, usize> = HashMap::from([(start, 0)]);
    let mut queue: VecDeque<Crd> = VecDeque::from([start]);

    while let Some(p) = queue.pop_front() {
        for q in adjacent(p) {
            if !distance.contains_key(&q) && distance[&p] < 20 {
                if q == end {
                    return distance[&p] + 1;
                }

                if grid[q.0][q.1] == '#' {
                    distance.insert(q, distance[&p] + 1);
                    queue.push_back(q);
                }
            }
        }
    }

    INF
}

// fn eprintln_grid(grid: &[Vec<char>]) {
//     for row in grid {
//         eprintln!("{}", row.iter().collect::<String>());
//     }
//     eprintln!();
// }

fn main() {
    let grid: Vec<Vec<char>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let crd_of = |c: char| -> Crd {
        for (i, row) in grid.iter().enumerate() {
            if let Some(j) = row.iter().position(|&x| x == c) {
                return Crd(i, j);
            }
        }
        panic!();
    };

    let start = crd_of('S');
    let end = crd_of('E');
    let initial_path = optimal_path(&grid, start, end);
    let initial_distance = initial_path.len() - 1;
    eprintln!("initial_distance:{}", initial_distance);

    let savings: Vec<usize> = initial_path
        .iter()
        .cloned()
        .enumerate()
        .combinations(2)
        .filter(|iajb| {
            let [(i, _), (j, _)] = iajb[..] else { panic!() };
            j - i > 20
        })
        .map(|iajb| {
            let [(i, a), (j, b)] = iajb[..] else { panic!() };
            let warp = optimal_distance_in_the_walls_under_20(&grid, a, b);
            (j - i).saturating_sub(warp)
        })
        .collect();

    let mut fq = savings
        .iter()
        .filter(|&&d| d >= 50)
        .counts()
        .into_iter()
        .collect::<Vec<_>>();
    fq.sort();
    eprintln!("{:?}", fq);

    let result = savings.iter().filter(|&&d| d >= 100).count();
    println!("{}", result);
}
