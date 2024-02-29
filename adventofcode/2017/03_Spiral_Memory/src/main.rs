fn containing_diameter(n: u32) -> u32 {
    let sqr = (n as f64).sqrt() as u32;
    let mut result = sqr.saturating_sub(2);
    while result % 2 == 0 || result * result < n {
        result += 1;
    }
    result
}

fn lowest_on_perimeter(d: u32) -> u32 {
    assert!(d > 0 && d % 2 == 1);
    if d == 1 {
        1
    } else {
        (d - 2) * (d - 2) + 1
    }
}

fn steps_to_access_port(n: u32) -> u32 {
    if n == 1 {
        0
    } else {
        let d = containing_diameter(n);
        let lo = lowest_on_perimeter(d);
        let nn = (n - lo) % (d - 1);
    }
}

fn main() {
    let n: u32 = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .parse()
        .unwrap();
    println!("{}", steps_to_access_port(n));
}
