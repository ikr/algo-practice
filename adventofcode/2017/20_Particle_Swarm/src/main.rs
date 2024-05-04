fn decode_triple(src: &str) -> [i64; 3] {
    let parts: Vec<String> = src.split(',').map(|x| x.to_string()).collect();
    assert!(parts.len() == 3);
    parts
        .into_iter()
        .map(|s| s.parse::<i64>().unwrap())
        .collect::<Vec<i64>>()
        .try_into()
        .unwrap()
}

#[derive(Debug, Clone, Copy)]
struct Particle {
    p: [i64; 3],
    v: [i64; 3],
    a: [i64; 3],
}

impl Particle {
    fn manhattan_distance_from_origin(&self) -> i64 {
        self.p.iter().fold(0, |acc, x| acc + x.abs())
    }

    fn simulate_t_ticks(&self, t: i64) -> Particle {
        let mut result = self.clone();
        for i in 0..=3 {
            result.v[i] = self.v[i] + self.a[i] * t;
            result.p[i] = self.p[i] + result.v[i] * t;
        }
        result
    }
}

fn main() {
    println!("Hello, world!");
}
