use itertools::Itertools;
use regex::Regex;
use std::io::{self, BufRead};

const TOTAL_SPOONS: i8 = 100;
const M: usize = 4;

type Ingredient = (String, [i8; 5]);

fn parse_fact(src: &str) -> Ingredient {
    let re = Regex::new(r"^([A-Z][a-z]+): capacity (-?\d+), durability (-?\d+), flavor (-?\d+), texture (-?\d+), calories (-?\d+)$").unwrap();
    let caps = re.captures(src).unwrap();
    (
        caps[1].to_string(),
        caps.iter()
            .skip(2)
            .map(|x| x.unwrap().as_str().parse::<i8>().unwrap())
            .collect::<Vec<_>>()
            .try_into()
            .unwrap(),
    )
}

fn all_ratios(ingredients_count: usize) -> Vec<Vec<i8>> {
    assert!(ingredients_count > 1);
    (1..ingredients_count)
        .map(|_| (1..TOTAL_SPOONS as i64).collect::<Vec<_>>())
        .multi_cartesian_product()
        .filter(|xs| xs.iter().sum::<i64>() < 100)
        .map(|xs| {
            let mut v = xs.iter().map(|x| *x as i8).collect::<Vec<_>>();
            let s = v.iter().sum::<i8>();
            v.push(TOTAL_SPOONS - s);
            v
        })
        .collect()
}

fn property_value_in_a_recipe(
    ingredients: &[Ingredient],
    ratio: &[i8],
    property_index: usize,
) -> i64 {
    let ingredient_property_values = ingredients
        .iter()
        .map(|(_, xs)| xs[property_index] as i64)
        .collect::<Vec<_>>();

    ingredient_property_values
        .into_iter()
        .zip(ratio.iter())
        .map(|(x, k)| x * *k as i64)
        .sum()
}

fn score(ingredients: &[Ingredient], ratio: &[i8]) -> i64 {
    (0..M)
        .map(|i| property_value_in_a_recipe(ingredients, ratio, i))
        .fold(1, |acc, x| if x > 0 { acc * x } else { 0 })
}

fn main() {
    let ingredients: Vec<_> = io::stdin()
        .lock()
        .lines()
        .map(|line| parse_fact(&line.unwrap()))
        .collect();

    let rss = all_ratios(ingredients.len());
    let result = rss
        .into_iter()
        .filter(|rs| property_value_in_a_recipe(&ingredients, rs, M) == 500)
        .map(|rs| score(&ingredients, &rs))
        .max()
        .unwrap();
    println!("{}", result);
}
