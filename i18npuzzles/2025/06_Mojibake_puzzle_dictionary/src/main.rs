const SQUASH: char = '_';

fn squash_first_non_ascii_subsequence(subsequence_length: usize, xs: &[char]) -> Option<Vec<char>> {
    let i0 = xs
        .windows(subsequence_length)
        .position(|ys| ys.iter().all(|c| !c.is_ascii()))?;

    let mut result: Vec<char> = xs[..i0].to_vec();
    result.push(SQUASH);
    result.extend(&xs[i0 + subsequence_length..]);
    Some(result)
}

fn squash_all_non_ascii_subsequences(subsequence_length: usize, mut xs: Vec<char>) -> Vec<char> {
    while let Some(ys) = squash_first_non_ascii_subsequence(subsequence_length, &xs) {
        xs = ys
    }
    xs
}

fn matches(xs: &str, pattern: &str) -> bool {
    xs.chars().count() == pattern.chars().count()
        && xs
            .chars()
            .zip(pattern.chars())
            .all(|(x, y)| y == '.' || x == y)
}

fn matches_any(xs: &str, patterns: &[String]) -> bool {
    patterns.iter().any(|p| matches(xs, p))
}

fn main() {
    let lines: Vec<String> = std::fs::read_to_string("in1")
        .unwrap()
        .lines()
        .map(|line| line.to_string())
        .collect();

    let isep: usize = lines.iter().position(|s| s.is_empty()).unwrap();

    let words: Vec<(usize, String)> = lines[..isep]
        .iter()
        .enumerate()
        .map(|(i, s)| {
            let pos = i + 1;
            let mb_m: Option<usize> = if pos % 5 == 0 && pos % 3 == 0 {
                Some(4)
            } else if pos % 5 == 0 || pos % 3 == 0 {
                Some(2)
            } else {
                None
            };

            let cs = s.chars().collect();
            let xs: Vec<char> = if let Some(m) = mb_m {
                squash_all_non_ascii_subsequences(m, cs)
            } else {
                cs
            };
            (pos, xs.into_iter().collect())
        })
        .collect();

    let patterns: Vec<String> = lines[isep + 1..]
        .iter()
        .map(|s| s.trim().to_string())
        .collect();

    let result: usize = words
        .into_iter()
        .filter(|(_, s)| matches_any(s, &patterns))
        .map(|(pos, _)| pos)
        .sum();

    println!("{}", result);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn squash_first_non_ascii_subsequence_2_works() {
        for (arg, res) in [
            (vec![], None),
            (vec!['a', 'b', 'c'], None),
            (vec!['Ã', '«', 'x'], Some(vec!['_', 'x'])),
            (vec!['q', 'Ã', '«', 'p'], Some(vec!['q', '_', 'p'])),
            (vec!['w', 'Ã', '¶'], Some(vec!['w', '_'])),
        ] {
            assert_eq!(squash_first_non_ascii_subsequence(2, &arg), res)
        }
    }

    #[test]
    fn squash_first_non_ascii_subsequence_4_works() {
        for (arg, res) in [
            (vec![], None),
            (vec!['a', 'b', 'c'], None),
            (vec!['Ã', '', 'Â', '£', 'x'], Some(vec!['_', 'x'])),
            (
                vec!['p', 'Ã', '', 'Â', '£', 'q'],
                Some(vec!['p', '_', 'q']),
            ),
            (vec!['w', 'Ã', '', 'Â', '£'], Some(vec!['w', '_'])),
        ] {
            assert_eq!(squash_first_non_ascii_subsequence(4, &arg), res)
        }
    }

    #[test]
    fn squash_all_non_ascii_subsequences_works_a() {
        assert_eq!(
            squash_all_non_ascii_subsequences(
                4,
                "myÃÂ¶nteisemmÃÂ¤ssÃÂ¤sikÃÂ¶hÃÂ¤n"
                    .chars()
                    .collect::<Vec<_>>()
            ),
            "my_nteisemm_ss_sik_h_n".chars().collect::<Vec<_>>()
        );
    }

    #[test]
    fn squash_all_non_ascii_subsequences_works_b() {
        assert_eq!(
            squash_all_non_ascii_subsequences(2, "dardÃ©es".chars().collect::<Vec<_>>()),
            "dard_es".chars().collect::<Vec<_>>()
        );
    }

    #[test]
    fn squash_all_non_ascii_subsequences_works_c() {
        assert_eq!(
            squash_all_non_ascii_subsequences(2, "abc".chars().collect::<Vec<_>>()),
            "abc".chars().collect::<Vec<_>>()
        );
    }

    #[test]
    fn matches_works() {
        for (xs, pat, res) in [
            ("", "", true),
            ("abc", "...", true),
            ("oops", ".o..", true),
            ("oops", ".....", false),
            ("oops", ".z..", false),
            ("träffs", "....f.", true),
        ] {
            assert_eq!(matches(xs, pat), res);
        }
    }
}
