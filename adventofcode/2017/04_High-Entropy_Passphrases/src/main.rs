fn line_words(line: &str) -> Vec<String> {
    line.split_whitespace().map(|x| x.to_string()).collect()
}

fn unique_words_count(xs: &[String]) -> usize {
    let mut seen = std::collections::HashSet::new();
    for x in xs {
        seen.insert(x);
    }
    seen.len()
}

fn normalize(xs: &str) -> String {
    let mut cs: Vec<char> = xs.chars().collect();
    cs.sort();
    cs.into_iter().collect()
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
            .filter(|xs| unique_words_count(xs) == xs.len())
            .count()
    );

    let nxss: Vec<Vec<String>> = xss
        .iter()
        .map(|xs| xs.iter().map(|x| normalize(x)).collect())
        .collect();

    println!(
        "{}",
        nxss.iter()
            .filter(|xs| unique_words_count(xs) == xs.len())
            .count()
    );
}
