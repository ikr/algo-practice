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

    (0..h + w)
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
        .map(|(crd, _)| crd)
        .collect()
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

    eprintln!("{:?}", grid);

    let programs: Vec<Vec<Dir>> = lines[isep + 1..]
        .iter()
        .map(|s| s.chars().map(Dir::decode).collect())
        .collect();

    eprintln!("{:?}", programs);

    let tr = trajectory(&grid, &programs[0], Crd(0, (4 - 1) * 2));
    eprintln!("{:?}", tr);
}
