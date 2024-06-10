use crop::Rope;

#[derive(Debug)]
struct RepeatOp {
    length: usize,
    times: usize,
}

impl RepeatOp {
    fn apply(&self, xs: &mut Rope, i0: usize) -> usize {
        let pat: String = xs.byte_slice(i0..i0 + self.length).chars().collect();
        let ys = pat.repeat(self.times);
        xs.delete(i0..i0 + self.length);
        let n = ys.len();
        xs.insert(i0, ys);
        i0 + n
    }
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

fn main() {
    let mut xs: Rope = Rope::from(
        std::io::read_to_string(std::io::stdin())
            .unwrap()
            .trim_end(),
    );

    let mut i0: usize = 0;
    loop {
        let it = xs
            .chars()
            .enumerate()
            .skip(i0)
            .skip_while(|(_, x)| *x != '(');

        if let Some((i, _)) = it.peekable().peek() {
            let jt = xs
                .chars()
                .enumerate()
                .skip(*i)
                .skip_while(|(_, x)| *x != ')');

            let (j, _) = *jt.peekable().peek().unwrap();
            let m = j - i + 1;
            let op = decode_marker(&xs.byte_slice(*i..=j).chars().collect::<String>());
            xs.delete(*i..=j);
            i0 = op.apply(&mut xs, j + 1 - m);
        } else {
            break;
        }
    }

    eprintln!("{:?}", xs);
    println!("{}", xs.byte_len());
}
