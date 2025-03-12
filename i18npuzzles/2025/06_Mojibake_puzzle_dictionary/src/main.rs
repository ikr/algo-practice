fn main() {
    let lines: Vec<String> = std::fs::read_to_string("inA")
        .unwrap()
        .lines()
        .map(|line| line.to_string())
        .collect();

    let isep: usize = lines.iter().position(|s| s.is_empty()).unwrap();

    eprintln!("{:?}", lines);
    eprintln!("isep:{}", isep);
}
