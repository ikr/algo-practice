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

fn solve_part_2(mut xs: Vec<i32>) {
    let mut steps: u32 = 0;
    let mut ip: i32 = 0;
    loop {
        steps += 1;
        let offset = xs[ip as usize];
        let next_ip = ip + offset;
        if next_ip < 0 || next_ip >= xs.len() as i32 {
            break;
        }
        xs[ip as usize] += if offset >= 3 { -1 } else { 1 };
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

    solve_part_1(xs.clone());
    solve_part_2(xs);
}
