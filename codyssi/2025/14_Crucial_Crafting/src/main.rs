use regex::Regex;
use std::io::{BufRead, stdin};

const MAX_COST: usize = 30;
const MAX_UNIQUE_MATERIALS: usize = 150;

#[derive(Debug)]
struct Item {
    quality: i32,
    cost: usize,
    unique_materials: usize,
}

impl Item {
    fn parse(s: &str) -> Item {
        let re =
            Regex::new(r"^\d+ \w+ \| Quality : (\d+), Cost : (\d+), Unique Materials : (\d+)$")
                .unwrap();

        let caps = re.captures(s).unwrap();
        let quality: i32 = caps[1].parse().unwrap();
        let cost: usize = caps[2].parse().unwrap();
        let unique_materials: usize = caps[3].parse().unwrap();

        Item {
            quality,
            cost,
            unique_materials,
        }
    }
}

fn main() {
    let items: Vec<Item> = stdin()
        .lock()
        .lines()
        .map(|line| Item::parse(&line.unwrap()))
        .collect();
    let n = items.len();

    // dp[i][j][k] is the maximum quality up to item i with j cost and k unique materials
    let mut dp: Vec<Vec<Vec<i32>>> = vec![vec![vec![0; MAX_UNIQUE_MATERIALS + 1]; MAX_COST + 1]; n];
    dp[0][items[0].cost][items[0].unique_materials] = items[0].quality;

    for i in 1..n {
        for j in 0..=MAX_COST {
            for k in 0..=MAX_UNIQUE_MATERIALS {
                dp[i][j][k] = dp[i - 1][j][k];
                if j >= items[i].cost && k >= items[i].unique_materials {
                    dp[i][j][k] = dp[i][j][k].max(
                        dp[i - 1][j - items[i].cost][k - items[i].unique_materials]
                            + items[i].quality,
                    );
                }
            }
        }
    }

    let mut max_quality = 0;
    let mut least_unique_materials = MAX_UNIQUE_MATERIALS;
    for i in 0..n {
        for j in 0..=MAX_COST {
            for k in 0..=MAX_UNIQUE_MATERIALS {
                if dp[i][j][k] == max_quality && k < least_unique_materials {
                    max_quality = dp[i][j][k];
                    least_unique_materials = k;
                } else if dp[i][j][k] > max_quality {
                    max_quality = dp[i][j][k];
                    least_unique_materials = k;
                }
            }
        }
    }

    let result = max_quality * least_unique_materials as i32;
    println!("{}", result);
}
