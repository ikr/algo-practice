fn solve_part_1(mut xs: Vec<i32>) {
    let mut steps: u32 = 0;
    let mut ip: i32 = 0;
    loop {
        steps += 1;
        let next_ip = ip + xs[ip as usize];
        if next_ip < 0 || next_ip >= xs.len() as i32 {
            break;
        }
        xs[ip as usize] += 1;
        ip = next_ip;
    }
    println!("{}", steps);
}

fn main() {
    let xs: Vec<i32> = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .lines()
        .map(|x| x.parse().unwrap())
        .collect();

    solve_part_1(xs);
}
