const H: usize = 40;

fn next_line(xs: &[u8]) -> Vec<u8> {
    let n = xs.len();
    let mut result = vec![b'.'; n];
    for i in 0..n {
        let left = if i > 0 { xs[i - 1] } else { b'.' };
        let right = if i < n - 1 { xs[i + 1] } else { b'.' };

        if (left == b'^') ^ (right == b'^') {
            result[i] = b'^';
        }
    }
    result
}

fn main() {
    let first_row: String = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .to_owned();

    let mut grid: Vec<Vec<u8>> = vec![first_row.into_bytes()];
    for _ in 1..H {
        grid.push(next_line(grid.last().unwrap()));
    }

    let safe_tiles_num = grid.iter().fold(0, |total, row| {
        total
            + row.iter().fold(
                0,
                |subtotal, x| if *x == b'.' { subtotal + 1 } else { subtotal },
            )
    });

    for row in grid {
        eprintln!("{}", String::from_utf8(row).unwrap());
    }

    println!("{}", safe_tiles_num);
}
