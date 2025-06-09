use std::io::{BufRead, stdin};

#[derive(Clone, Copy, Debug, PartialEq)]
struct Node(u16, char);

fn parse_node(s: &str) -> Node {
    let kv = s.split('=').collect::<Vec<_>>();
    let vv = kv[1]
        .strip_prefix('[')
        .and_then(|a| a.strip_suffix(']'))
        .unwrap();
    let rank_symbol = vv.split(',').collect::<Vec<_>>();
    Node(
        rank_symbol[0].parse().unwrap(),
        rank_symbol[1].chars().next().unwrap(),
    )
}

fn parse_line(s: &str) -> [Node; 2] {
    let parts = s.split_whitespace().collect::<Vec<_>>();
    [parse_node(parts[2]), parse_node(parts[3])]
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let node_pairs: Vec<_> = lines.into_iter().map(|s| parse_line(&s)).collect();
    eprintln!("{:?}", node_pairs);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_parse_noed() {
        assert_eq!(parse_node("left=[146,E]"), Node(146, 'E'));
        assert_eq!(parse_node("right=[283,!]"), Node(283, '!'));
    }
}
