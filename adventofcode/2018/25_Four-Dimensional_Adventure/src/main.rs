type Quad = [i32; 4];

fn parse_quad(src: &str) -> Quad {
    let xs: Vec<i32> = src.split(',').map(|s| s.trim().parse().unwrap()).collect();
    xs.try_into().unwrap()
}

fn read_input() -> Vec<Quad> {
    let input = std::io::read_to_string(std::io::stdin()).unwrap();
    input.lines().map(parse_quad).collect()
}

fn main() {
    eprintln!("{:?}", read_input());
}
