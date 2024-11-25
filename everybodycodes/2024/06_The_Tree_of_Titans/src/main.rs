use std::{
    collections::VecDeque,
    io::{self, BufRead},
};

fn parse_line(line: &str) -> (String, Vec<String>) {
    let parts = line.split(":").collect::<Vec<_>>();
    let lhs = parts[0].to_string();
    let rhs = parts[1]
        .split(",")
        .map(|s| s.to_string())
        .collect::<Vec<_>>();
    (lhs, rhs)
}

fn adjacent_of(g_src: &[(String, Vec<String>)], node: &str) -> Vec<String> {
    g_src
        .iter()
        .filter(|(src, _)| src == node)
        .flat_map(|(_, dsts)| dsts)
        .map(|s| s.to_string())
        .collect()
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap())
        .collect();

    let g_src = lines
        .into_iter()
        .map(|l| parse_line(&l))
        .collect::<Vec<_>>();

    let mut q: VecDeque<Vec<String>> = VecDeque::new();
    q.push_back(vec!["RR".to_string()]);

    while let Some(u) = q.pop_front() {
        if u.last().unwrap() == "@" {
            println!("{}", u.join(""));
            continue;
        }

        for v in adjacent_of(&g_src, u.last().unwrap()) {
            let mut u_new = u.clone();
            u_new.push(v);
            q.push_back(u_new);
        }
    }
}
