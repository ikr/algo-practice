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

fn main() {
    let lines: Vec<String> = std::fs::read_to_string("inA")
        .unwrap()
        .lines()
        .map(|line| line.to_string())
        .collect();

    let isep: usize = lines.iter().position(|s| s.is_empty()).unwrap();

    eprintln!("{:?}", lines);
    eprintln!("isep:{}", isep);
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
}
