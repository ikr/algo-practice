use std::io::{self, Read};

fn lowest_layer(num_levels: i64) -> i64 {
    1 + (num_levels - 1) * 2
}

fn main() {
    let mut buf = String::new();
    io::stdin().read_to_string(&mut buf).unwrap();
    let initial_number_of_blocks: i64 = buf.trim().parse().unwrap();

    let mut h: i64 = 1;
    loop {
        let an = lowest_layer(h);
        let s = ((1 + an) * h) / 2;
        if s >= initial_number_of_blocks {
            break;
        }
        h += 1;
    }

    let s = ((1 + lowest_layer(h)) * h) / 2;
    let missing = s - initial_number_of_blocks;
    let result = missing * lowest_layer(h);
    println!("{}", result);
}
