use std::{
    fmt::Debug,
    io::{self, BufRead},
    str::FromStr,
};

fn decode<T>(src: &str) -> T
where
    T: FromStr,
    T::Err: Debug,
{
    src.parse::<T>().expect(&format!("Can't parse {}", src))
}

fn decode_csv<T>(src: &str) -> Vec<T>
where
    T: FromStr,
    T::Err: Debug,
{
    src.split(',').map(|a| decode(a)).collect()
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|x| x.expect("stdin line read"))
        .collect();

    let xss: Vec<Vec<u16>> = lines.into_iter().map(|line| decode_csv(&line)).collect();

    eprintln!("{:?}", xss);
}
