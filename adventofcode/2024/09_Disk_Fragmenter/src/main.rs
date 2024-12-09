use std::{
    collections::VecDeque,
    io::{self, BufRead},
};

#[derive(Clone, Copy, Debug, Eq, PartialEq)]
enum Content {
    File(usize),
    Empty,
}

fn empty_space_length(xs: &VecDeque<Content>, i0: usize) -> usize {
    assert_eq!(xs[i0], Content::Empty);
    let mut i = i0;
    while i + 1 < xs.len() && xs[i + 1] == Content::Empty {
        i += 1;
    }
    i - i0 + 1
}

fn backwards_content_length(xs: &VecDeque<Content>, i0: usize) -> usize {
    let Content::File(id0) = xs[i0] else { panic!() };
    let mut i = i0;
    while i != 0 && xs[i - 1] != Content::Empty {
        let Content::File(id) = xs[i - 1] else {
            panic!()
        };
        if id == id0 {
            i -= 1;
        } else {
            break;
        }
    }
    i0 - i + 1
}

fn backwards_content_begin(xs: &VecDeque<Content>, i0: usize) -> Option<usize> {
    let mut i = i0;
    loop {
        if xs[i] != Content::Empty {
            return Some(i);
        }
        if i == 0 {
            break;
        }
        i -= 1;
    }
    None
}

fn index_of_empty_space_large_enough(xs: &VecDeque<Content>, l: usize) -> Option<usize> {
    let mut i: usize = 0;
    while i < xs.len() {
        if xs[i] == Content::Empty && empty_space_length(xs, i) >= l {
            return Some(i);
        }
        i += 1;
    }
    None
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

    let mut mbj = backwards_content_begin(&xs, xs.len() - 1);
    while let Some(j) = mbj {
        let m = backwards_content_length(&xs, j);
        if let Some(i) = index_of_empty_space_large_enough(&xs, m) {
            if i + m - 1 < j {
                let Content::File(id) = xs[j] else { panic!() };
                for jj in j + 1 - m..=j {
                    xs[jj] = Content::Empty;
                }
                for ii in i..i + m {
                    xs[ii] = Content::File(id);
                }
            }
        }

        if j == m - 1 {
            break;
        }

        mbj = backwards_content_begin(&xs, j - m);
    }

    let result: usize = xs
        .into_iter()
        .map(|c| match c {
            Content::File(x) => x,
            Content::Empty => 0,
        })
        .enumerate()
        .map(|(i, x)| i * x)
        .sum();
    println!("{}", result);
}
