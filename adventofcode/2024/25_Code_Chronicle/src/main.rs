fn transpose<T>(grid: Vec<Vec<T>>) -> Vec<Vec<T>> {
    assert!(!grid.is_empty());
    let h = grid[0].len();
    let mut iters: Vec<_> = grid.into_iter().map(|n| n.into_iter()).collect();
    (0..h)
        .map(|_| {
            iters
                .iter_mut()
                .map(|n| n.next().unwrap())
                .collect::<Vec<T>>()
        })
        .collect()
}

fn parse_grid(s: &str) -> Vec<Vec<char>> {
    s.lines().map(|x| x.chars().collect()).collect()
}

fn pounds_num(xs: &[char]) -> usize {
    xs.iter().filter(|&&c| c == '#').count()
}

fn digest(g: &[Vec<char>]) -> Vec<usize> {
    transpose(g.to_vec())
        .iter()
        .map(|row| pounds_num(row))
        .collect::<Vec<_>>()
}

fn fit(lock: &[usize], key: &[usize]) -> bool {
    lock.iter()
        .zip(key.iter())
        .map(|(x, y)| x + y)
        .all(|x| x < 6)
}

fn main() {
    let input: String = std::io::read_to_string(std::io::stdin()).unwrap();
    let grids: Vec<Vec<Vec<char>>> = input.split("\n\n").map(parse_grid).collect();
    let locks: Vec<Vec<usize>> = grids
        .iter()
        .filter(|g| g[0][0] == '#')
        .map(|g| digest(&g[1..]))
        .collect();

    let keys: Vec<Vec<usize>> = grids
        .iter()
        .filter(|g| g[0][0] == '.')
        .map(|g| digest(&g[0..g.len() - 1]))
        .collect();

    let mut result = 0;
    for l in locks.iter() {
        for k in keys.iter() {
            if fit(l, k) {
                result += 1;
            }
        }
    }
    println!("{}", result);
}
