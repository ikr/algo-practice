use std::io::Read;

fn value_of(c: char) -> i32 {
    (if c.is_ascii_lowercase() {
        ((c as u8) - b'a') + 1
    } else {
        assert!(c.is_ascii_uppercase());
        ((c as u8) - b'A') + 27
    }) as i32
}

fn normalize(mut x: i32) -> i32 {
    while x < 1 {
        x += 52;
    }
    while x > 52 {
        x -= 52;
    }
    x
}

fn main() {
    let mut input = String::new();
    std::io::stdin().read_to_string(&mut input).unwrap();
    input = input.trim().to_string();

    let cs: Vec<char> = input.chars().collect();
    let mut vs: Vec<i32> = vec![0; cs.len()];
    vs[0] = value_of(cs[0]);

    for i in 1..cs.len() {
        if cs[i].is_alphabetic() {
            vs[i] = value_of(cs[i]);
        } else {
            vs[i] = normalize(vs[i - 1] * 2 - 5);
        }
    }

    println!("{}", vs.iter().sum::<i32>());
}
