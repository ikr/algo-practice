#[derive(Debug)]
enum Dir {
    N,
    NE,
    SE,
    S,
    SW,
    NW,
}

impl Dir {
    fn parse(src: &str) -> Dir {
        match src {
            "n" => Dir::N,
            "ne" => Dir::NE,
            "se" => Dir::SE,
            "s" => Dir::S,
            "sw" => Dir::SW,
            "nw" => Dir::NW,
            _ => panic!("Invalid Dir source {}", src),
        }
    }
}

fn main() {
    let ds: Vec<Dir> = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .split(",")
        .map(Dir::parse)
        .collect();

    eprintln!("{:?}", ds);
}
