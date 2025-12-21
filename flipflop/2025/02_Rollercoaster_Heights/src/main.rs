use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).unwrap();

    let deltas: Vec<i32> = buf
        .trim_end()
        .chars()
        .map(|c| match c {
            '^' => 1,
            'v' => -1,
            _ => unreachable!(),
        })
        .collect();

    let result = deltas
        .into_iter()
        .scan(0, |state, x| {
            *state += x;
            Some(*state)
        })
        .max()
        .unwrap();

    eprintln!("{result}");
}
