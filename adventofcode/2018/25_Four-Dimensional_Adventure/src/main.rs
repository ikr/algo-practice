use ac_library::Dsu;

type Quad = [i32; 4];

fn parse_quad(src: &str) -> Quad {
    let xs: Vec<i32> = src.split(',').map(|s| s.trim().parse().unwrap()).collect();
    xs.try_into().unwrap()
}

fn read_input() -> Vec<Quad> {
    let input = std::io::read_to_string(std::io::stdin()).unwrap();
    input.lines().map(parse_quad).collect()
}

fn manhattan(a: &Quad, b: &Quad) -> i32 {
    a.iter().zip(b.iter()).map(|(x, y)| (x - y).abs()).sum()
}

fn main() {
    let qs = read_input();
    let n = qs.len();
    let mut dsu = Dsu::new(n);

    for (i, q) in qs.iter().enumerate() {
        for j in 0..i {
            if manhattan(q, &qs[j]) <= 3 {
                dsu.merge(i, j);
            }
        }
    }

    eprintln!("{:?}", dsu.groups());
    println!("{}", dsu.groups().len());
}
