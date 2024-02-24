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
    let mut seq = 0;
    let mut components: Vec<i32> = vec![0; qs.len()];

    for (i, q) in qs.iter().enumerate() {
        let mut cur = 0;
        for j in 0..i {
            if manhattan(q, &qs[j]) <= 3 {
                cur = components[j];
                break;
            }
        }
        if cur == 0 {
            seq += 1;
            cur = seq;
        }
        components[i] = cur;
    }

    eprintln!("{:?}", components);
    println!("{}", seq);
}
