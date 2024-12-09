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

fn pop_tail_content(xs: &mut VecDeque<Content>) -> Vec<Content> {
    let Content::File(id0) = *(xs.back().unwrap()) else {
        panic!()
    };

    let mut result = vec![];
    while let Some(Content::File(id)) = xs.back() {
        if *id == id0 {
            result.push(Content::File(*id));
            xs.pop_back();
        } else {
            break;
        }
    }
    result
}

fn tail_content_length(xs: &VecDeque<Content>) -> usize {
    let Content::File(id0) = xs.back().unwrap() else {
        panic!()
    };
    let n = xs.len();
    let mut i = n - 1;
    while i != 0 && xs[i - 1] != Content::Empty {
        let Content::File(id) = xs[i - 1] else {
            panic!()
        };
        if id == *id0 {
            i -= 1;
        } else {
            break;
        }
    }
    n - i
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

    eprintln!("{:?} {}", xs, tail_content_length(&xs));
    let tail = pop_tail_content(&mut xs);
    eprintln!("{:?}", tail);
    eprintln!("{:?}", index_of_empty_space_large_enough(&xs, 21));

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
