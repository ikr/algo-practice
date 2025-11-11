use std::io::Read;

fn mentor_symbol(x: u8) -> u8 {
    x.to_ascii_uppercase()
}

fn is_novice_symbol(x: u8) -> bool {
    x.is_ascii_lowercase()
}

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).unwrap();
    let xs: Vec<u8> = buf.trim().bytes().collect();

    let result = xs
        .into_iter()
        .fold((vec![0usize; 128], 0), |(mut fq, s), x| {
            if is_novice_symbol(x) {
                let xx = mentor_symbol(x);
                (fq.clone(), s + fq[xx as usize])
            } else {
                fq[x as usize] += 1;
                (fq, s)
            }
        });

    println!("{}", result.1);
}
