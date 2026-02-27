use proconio::input;
use std::{
    collections::HashMap,
    io::{BufWriter, Write, stdout},
};

fn num_pairings(pqs: Vec<(u32, u32)>) -> usize {
    let mut sz_by_team_by_sport: HashMap<u32, HashMap<u32, usize>> = HashMap::new();

    for (p, q) in pqs {
        sz_by_team_by_sport
            .entry(p)
            .and_modify(|sz_by_team| {
                sz_by_team
                    .entry(q)
                    .and_modify(|sz| {
                        *sz += 1;
                    })
                    .or_insert(1);
            })
            .or_insert(HashMap::from([(q, 1)]));
    }

    let totals_by_sport: HashMap<u32, usize> = sz_by_team_by_sport
        .iter()
        .map(|(p, sz_by_team)| (*p, sz_by_team.values().sum()))
        .collect();

    let mut result = 0;

    for (p, sz_by_team) in sz_by_team_by_sport {
        let total: usize = *totals_by_sport.get(&p).unwrap();

        for (_, sz) in sz_by_team {
            result += sz * (total - sz);
        }
    }

    result / 2
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        pqs: [(u32, u32); n],
    }

    let result = num_pairings(pqs);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
