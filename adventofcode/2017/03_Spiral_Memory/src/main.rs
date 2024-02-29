fn containing_diameter(n: i64) -> i64 {
    let sqr = (n as f64).sqrt() as i64;
    let mut result = sqr - 2;
    while result < 0 || result % 2 == 0 || result * result < n {
        result += 1;
    }
    result
}

fn lowest_on_perimeter(d: i64) -> i64 {
    assert!(d > 0 && d % 2 == 1);
    if d == 1 {
        1
    } else {
        (d - 2) * (d - 2) + 1
    }
}

fn steps_to_access_port(n: i64) -> i64 {
    if n == 1 {
        0
    } else {
        let d = containing_diameter(n);
        let lo = lowest_on_perimeter(d);
        let nn = (n - lo) % (d - 1);

        assert!((d - 1) % 2 == 0);
        let side_center = (d - 1) / 2 - 1;
        d / 2 + (nn - side_center).abs()
    }
}

fn main() {
    let n: i64 = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .parse()
        .unwrap();
    println!("{}", steps_to_access_port(n));
}
