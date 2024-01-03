fn main() {
    let offset: usize = 702831;

    let mut xs: Vec<u8> = vec![3, 7];
    let mut i: usize = 0;
    let mut j: usize = 1;

    while xs.len() < offset + 10 {
        let x = xs[i] + xs[j];
        if x > 9 {
            xs.push(1);
            xs.push(x % 10);
        } else {
            xs.push(x);
        }

        i = (i + xs[i] as usize + 1) % xs.len();
        j = (j + xs[j] as usize + 1) % xs.len();

        if xs.len() >= offset + 10 {
            break;
        }
    }

    let ys = &xs[offset..offset + 10];
    let result = ys.iter().map(|x| x.to_string()).collect::<String>();

    println!("{}", result);
}
