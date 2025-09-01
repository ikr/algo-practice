use itertools::Itertools;
use itertools::MinMaxResult::{MinMax, NoElements, OneElement};
use memoise::memoise;
use std::io::{BufRead, stdin};

#[derive(Clone, Copy, Debug)]
enum Dir {
    L,
    R,
}

impl Dir {
    fn decode(x: char) -> Self {
        match x {
            'L' => Self::L,
            'R' => Self::R,
            _ => unreachable!(),
        }
    }
}

#[derive(Clone, Copy, Debug)]
struct Crd(usize, usize);

impl Crd {
    fn get(self, grid: &[Vec<u8>]) -> u8 {
        let h = grid.len();
        assert_ne!(h, 0);
        let w = grid[0].len();
        assert_ne!(w, 0);

        assert!(self.0 < h);
        assert!(self.1 < w);
        grid[self.0][self.1]
    }
}

fn trajectory(grid: &[Vec<u8>], bounce_program: &[Dir], start: Crd) -> Vec<Crd> {
    assert_ne!(start.get(grid), 1);
    let h = grid.len();
    let w = grid[0].len();
    let q0: Vec<Dir> = bounce_program.iter().rev().cloned().collect();

    let movement_coordinates = (0..h + w)
        .scan((start, q0), |(crd, q), _| {
            if crd.get(grid) == 1 {
                match q.pop().unwrap() {
                    Dir::L if crd.1 != 0 => crd.1 -= 1,
                    Dir::L => crd.1 += 1,
                    Dir::R if crd.1 != w - 1 => crd.1 += 1,
                    Dir::R => crd.1 -= 1,
                }
            } else {
                crd.0 += 1;
            }

            if crd.0 == h {
                None
            } else {
                Some((*crd, q.clone()))
            }
        })
        .map(|(crd, _)| crd);

    std::iter::once(start).chain(movement_coordinates).collect()
}

fn toss_column(toss_slot_number: usize) -> usize {
    (toss_slot_number - 1) * 2
}

fn final_slot_number(final_column: usize) -> usize {
    final_column / 2 + 1
}

fn toss_slots_count(grid_width: usize) -> usize {
    grid_width.div_ceil(2)
}

fn coins_won(toss_slot: usize, final_slot: usize) -> usize {
    (final_slot * 2).saturating_sub(toss_slot)
}

#[memoise(memo_bounce_program_index < 6, toss_slot <= 20)]
fn simulate_toss_return_coins_won(
    grid: &[Vec<u8>],
    bounce_program: &[Dir],
    memo_bounce_program_index: usize,
    toss_slot: usize,
) -> usize {
    let tr = trajectory(grid, bounce_program, Crd(0, toss_column(toss_slot)));
    coins_won(toss_slot, final_slot_number(tr.last().unwrap().1))
}

fn simulate_game_return_coins_won(
    grid: &[Vec<u8>],
    bounce_programs: &[Vec<Dir>],
    toss_slots_by_program_index: Vec<usize>,
) -> usize {
    bounce_programs
        .iter()
        .enumerate()
        .zip(toss_slots_by_program_index)
        .map(|((ipr, pr), toss_slot)| simulate_toss_return_coins_won(grid, pr, ipr, toss_slot))
        .sum()
}

fn simalate_all_game_permutations_return_minmax_coins_won(
    grid: &[Vec<u8>],
    bounce_programs: &[Vec<Dir>],
    toss_slots: Vec<usize>,
) -> (usize, usize) {
    let n = toss_slots.len();
    match toss_slots
        .into_iter()
        .permutations(n)
        .map(|toss_slots_by_program_index| {
            simulate_game_return_coins_won(grid, bounce_programs, toss_slots_by_program_index)
        })
        .minmax()
    {
        OneElement(a) => (a, a),
        MinMax(lo, hi) => (lo, hi),
        NoElements => unreachable!(),
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    assert_ne!(lines.len(), 0);
    let grid_width = lines[0].len();
    let isep = lines.iter().position(|s| s.is_empty()).unwrap();

    let grid: Vec<Vec<u8>> = std::iter::once(vec![0; grid_width])
        .chain(
            lines[..isep]
                .iter()
                .map(|s| s.chars().map(|c| if c == '*' { 1 } else { 0 }).collect()),
        )
        .collect();

    let programs: Vec<Vec<Dir>> = lines[isep + 1..]
        .iter()
        .map(|s| s.chars().map(Dir::decode).collect())
        .collect();

    let n = toss_slots_count(grid_width);
    let m = programs.len();

    let mut lo: usize = usize::MAX;
    let mut hi: usize = 0;

    for toss_slots in (1..=n).combinations(m) {
        let (a, b) =
            simalate_all_game_permutations_return_minmax_coins_won(&grid, &programs, toss_slots);

        lo = lo.min(a);
        hi = hi.max(b);
    }

    println!("{lo} {hi}");
}
