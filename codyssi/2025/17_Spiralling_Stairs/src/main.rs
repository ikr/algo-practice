use std::io::{BufRead, stdin};

const B: usize = 200;

fn parse_main_staircase_end(s: &str) -> usize {
    let ps: Vec<_> = s.split(" : ").collect();
    assert_eq!(ps.len(), 3);

    let ab: Vec<usize> = ps[1].split(" -> ").map(|x| x.parse().unwrap()).collect();
    assert_eq!(ab.len(), 2);
    assert_eq!(ab[0], 0);

    ab[1]
}

#[derive(Clone, Copy, Debug)]
struct StaircaseBranch {
    id: usize,
    steps_range: (usize, usize),
    source_id: usize,
    destination_id: usize,
}

impl StaircaseBranch {
    fn parse_id(s: &str) -> usize {
        s.strip_prefix("S").unwrap().parse::<usize>().unwrap() - 1
    }

    fn parse_source_and_destination(s: &str) -> (usize, usize) {
        let ps: Vec<_> = s.split_whitespace().collect();
        assert_eq!(ps.len(), 4);
        (Self::parse_id(ps[1]), Self::parse_id(ps[3]))
    }

    fn parse(s: &str) -> Self {
        let ps: Vec<_> = s.split(" : ").collect();
        assert_eq!(ps.len(), 3);
        let id = Self::parse_id(ps[0]);

        let ab: Vec<usize> = ps[1].split(" -> ").map(|x| x.parse().unwrap()).collect();
        assert_eq!(ab.len(), 2);
        let steps_range = (ab[0], ab[1]);

        let (source_id, destination_id) = Self::parse_source_and_destination(ps[2]);
        Self {
            id,
            steps_range,
            source_id,
            destination_id,
        }
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let n = parse_main_staircase_end(&lines[0]) + 1;
    let m = lines.len() - 2;

    let branches: Vec<StaircaseBranch> = lines[1..m]
        .iter()
        .map(|s| StaircaseBranch::parse(s))
        .collect();

    let magnitudes: Vec<usize> = lines
        .last()
        .and_then(|s| s.strip_prefix("Possible Moves : "))
        .unwrap()
        .split(", ")
        .map(|x| x.parse().unwrap())
        .collect();

    eprintln!(
        "{} steps, {} staircases\nbranches: {:?}\nmagnitudes: {:?}",
        n, m, branches, magnitudes
    );
}
