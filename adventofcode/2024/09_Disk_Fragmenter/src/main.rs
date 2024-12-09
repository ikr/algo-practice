use std::{
    collections::VecDeque,
    io::{self, BufRead},
};

#[derive(Clone, Copy, Debug, Eq, PartialEq)]
enum Content {
    File(usize),
    Empty,
}

fn main() {
    let lines: Vec<Vec<u8>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().bytes().collect())
        .collect();
    let src = lines[0].clone();

    let mut xs: VecDeque<Content> = VecDeque::new();
    for (i, x) in src.into_iter().enumerate() {
        let id = i / 2;
        let v: Content = if i % 2 == 0 {
            Content::File(id)
        } else {
            Content::Empty
        };
        let m = x - b'0';
        for _ in 0..m {
            xs.push_back(v);
        }
    }

    eprintln!("{:?}", xs);

    let mut mbi: Option<usize> = xs.iter().position(|x| *x == Content::Empty);
    while let Some(mut i) = mbi {
        while Some(&Content::Empty) == xs.back() {
            xs.pop_back();
        }
        if i >= xs.len() {
            break;
        }

        let Content::File(id) = *xs.back().unwrap() else {
            panic!()
        };
        xs.pop_back();
        xs[i] = Content::File(id);

        loop {
            if i + 1 < xs.len() {
                if xs[i + 1] == Content::Empty {
                    mbi = Some(i + 1);
                    break;
                } else {
                    i += 1;
                }
            } else {
                mbi = None;
                break;
            }
        }
    }

    eprintln!("{:?}", xs);

    let result: usize = xs
        .into_iter()
        .map(|c| match c {
            Content::File(x) => x,
            Content::Empty => panic!(),
        })
        .enumerate()
        .map(|(i, x)| i * x)
        .sum();
    println!("{}", result);
}
