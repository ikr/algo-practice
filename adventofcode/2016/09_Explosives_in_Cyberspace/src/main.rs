use crop::Rope;

fn main() {
    let xs: Rope = Rope::from(
        std::io::read_to_string(std::io::stdin())
            .unwrap()
            .trim_end(),
    );

    eprintln!("{}", xs.byte_len());
}
