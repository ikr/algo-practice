use crop::Rope;

fn main() {
    let xs: Rope = Rope::from(
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
            eprintln!("{} {}", i, j);
            i0 = j;
        } else {
            break;
        }
    }

    eprintln!("{:?}", xs);
    println!("{}", xs.byte_len());
}
