struct RepeatOp {
    length: usize,
    times: usize,
}

fn decode_marker(src: &str) -> RepeatOp {
    let xs: Vec<usize> = src
        .strip_prefix('(')
        .unwrap()
        .strip_suffix(')')
        .unwrap()
        .split('x')
        .map(|x| x.parse().unwrap())
        .collect();
    let [length, times] = xs[..] else {
        panic!("{:?} isn't a pair", xs)
    };
    RepeatOp { length, times }
}

fn decompressed_size(xs: &str) -> usize {
    let mut result: usize = 0;
    let mut i0: usize = 0;
    while i0 < xs.len() {
        if xs.as_bytes()[i0] == b'(' {
            let jt = xs
                .bytes()
                .enumerate()
                .skip(i0)
                .skip_while(|(_, x)| *x != b')');
            let (j, _) = *jt.peekable().peek().unwrap();
            let m = j - i0 + 1;
            let op = decode_marker(&xs[i0..=j]);
            i0 += m + op.length;
            result += decompressed_size(&xs[j + 1..j + 1 + op.length]) * op.times;
        } else {
            result += 1;
            i0 += 1;
        }
    }
    result
}

fn main() {
    let xs: String = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim_end()
        .to_owned();

    println!("{}", decompressed_size(&xs));
}
