fn line_words(line: &str) -> Vec<String> {
    line.split_whitespace().map(|x| x.to_string()).collect()
}

fn unique_words_coung(xs: &[String]) -> usize {
    let mut seen = std::collections::HashSet::new();
    for x in xs {
        seen.insert(x);
    }
    seen.len()
}

fn main() {
    let xss: Vec<Vec<String>> = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .lines()
        .map(line_words)
        .collect();

    println!(
        "{}",
        xss.iter()
            .filter(|xs| unique_words_coung(xs) == xs.len())
            .count()
    );
}
