use std::collections::HashMap;
use std::io::{self, BufRead};

fn parse_vertices_csv(src: &str) -> Vec<String> {
    if src.is_empty() {
        vec![]
    } else {
        src.split(", ").map(|x| x.to_string()).collect()
    }
}

fn parse_id_and_weight(src: &str) -> (String, i32) {
    let parts: Vec<&str> = src.split(" (").collect();
    let id = parts[0].to_string();
    let weight: i32 = parts[1].strip_suffix(')').unwrap().parse().unwrap();
    (id, weight)
}

#[derive(Debug)]
struct VertexSpec {
    id: String,
    weight: i32,
    adjacent: Vec<String>,
}

impl VertexSpec {
    fn parse(src: &str) -> VertexSpec {
        let parts: Vec<&str> = src.split(" -> ").collect();
        let (id, weight) = parse_id_and_weight(parts[0]);
        let adjacent = parse_vertices_csv(parts.get(1).unwrap_or(&""));
        VertexSpec {
            id,
            weight,
            adjacent,
        }
    }
}

fn majority_value(xs: &HashMap<i32, i32>) -> i32 {
    assert!(xs.len() == 2);
    for (k, v) in xs {
        if *v > 1 {
            return *k;
        }
        assert!(*v == 1);
    }
    panic!("No majority");
}

struct BalanceExploration {
    adj: HashMap<String, Vec<String>>,
    wei: HashMap<String, i32>,
}

impl BalanceExploration {
    fn control_subtree_weight(&self, root: &str) -> i32 {
        let adj: &[String] = self.adj.get(root).unwrap();
        let w0 = *self.wei.get(root).unwrap();

        if adj.is_empty() {
            w0
        } else {
            let sub_wei: HashMap<String, i32> = adj.iter().fold(HashMap::new(), |mut acc, v| {
                acc.insert(v.clone(), self.control_subtree_weight(v));
                acc
            });

            let wei_freq: HashMap<i32, i32> =
                sub_wei.values().fold(HashMap::new(), |mut acc, w| {
                    *acc.entry(*w).or_insert(0) += 1;
                    acc
                });

            if wei_freq.len() > 1 {
                eprintln!("Unbalanced sub-trees: {:?}", sub_wei);
                let mv = majority_value(&wei_freq);
                for (k, v) in &sub_wei {
                    if *v != mv {
                        let dw = mv - *v;
                        let w = *self.wei.get(k).unwrap();
                        eprintln!("New weight of {}: {}", k, w + dw);
                        std::process::exit(0);
                    }
                }
            }

            w0 + sub_wei.values().sum::<i32>()
        }
    }
}

fn main() {
    let vs: Vec<VertexSpec> = io::stdin()
        .lock()
        .lines()
        .map(|line| VertexSpec::parse(&line.unwrap()))
        .collect();

    let mut root: Option<String> = None;

    {
        // Part 1
        let mut in_deg: HashMap<String, usize> = HashMap::new();

        for u in &vs {
            for v in &u.adjacent {
                *in_deg.entry(v.clone()).or_insert(0) += 1;
            }
        }

        for u in &vs {
            if in_deg.get(&u.id).is_none() {
                root = Some(u.id.clone());
                println!("{}", u.id);
            }
        }
    }

    {
        // Part 2
        let adj: HashMap<String, Vec<String>> = vs.iter().fold(HashMap::new(), |mut acc, u| {
            acc.insert(u.id.clone(), u.adjacent.clone());
            acc
        });

        let wei: HashMap<String, i32> = vs.iter().fold(HashMap::new(), |mut acc, u| {
            acc.insert(u.id.clone(), u.weight);
            acc
        });

        let be = BalanceExploration { adj, wei };
        be.control_subtree_weight(&root.unwrap());
    }
}
