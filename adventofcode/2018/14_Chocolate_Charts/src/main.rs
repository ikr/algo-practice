fn main() {
    let marker = "702831";

    let mut xs: Vec<u8> = vec![3, 7];
    let mut i: usize = 0;
    let mut j: usize = 1;

    for _ in 0..100_000_000 {
        let x = xs[i] + xs[j];
        if x > 9 {
            xs.push(1);
            xs.push(x % 10);
        } else {
            xs.push(x);
        }

        i = (i + xs[i] as usize + 1) % xs.len();
        j = (j + xs[j] as usize + 1) % xs.len();
    }

    let s = xs.iter().map(|x| x.to_string()).collect::<String>();
    let pos = s.find(marker).unwrap();
    println!("{}", pos);
}
