use std::{
    collections::BTreeMap,
    io::{self, BufRead},
};

use chrono::NaiveDate;

fn parse_date_source(s: &str) -> [i32; 3] {
    let parts: Vec<i32> = s.split('-').map(|x| x.parse().unwrap()).collect();
    parts.try_into().unwrap()
}

fn parse_names_list(s: &str) -> Vec<String> {
    s.split(", ").map(|x| x.to_string()).collect()
}

fn parse_line(s: &str) -> ([i32; 3], Vec<String>) {
    let parts: Vec<_> = s.split(": ").collect();
    (parse_date_source(parts[0]), parse_names_list(parts[1]))
}

fn infer_ymd_indices(tris: &[[i32; 3]]) -> [usize; 3] {
    for (y, m, d) in [(0, 1, 2), (0, 2, 1), (2, 0, 1), (2, 1, 0)] {
        if tris.iter().all(|tri| {
            NaiveDate::from_ymd_opt(
                if tri[y] > 20 {
                    1900 + tri[y]
                } else {
                    2000 + tri[y]
                },
                tri[m] as u32,
                tri[d] as u32,
            )
            .is_some()
        }) {
            return [y, m, d];
        }
    }
    panic!("Can't deduce the date parts in {:?}", tris);
}

fn main() {
    let lines: Vec<_> = io::stdin()
        .lock()
        .lines()
        .map(|line| parse_line(&line.unwrap()))
        .collect();

    let date_sources_by_name: BTreeMap<String, Vec<[i32; 3]>> =
        lines.iter().fold(BTreeMap::new(), |mut acc, (tri, names)| {
            for name in names {
                acc.entry(name.clone())
                    .and_modify(|tris| tris.push(*tri))
                    .or_insert(vec![*tri]);
            }
            acc
        });

    let ymd_indices_by_name: BTreeMap<String, [usize; 3]> = date_sources_by_name
        .iter()
        .map(|(name, tris)| (name.clone(), infer_ymd_indices(tris)))
        .collect();

    let dates_by_name: BTreeMap<String, Vec<[i32; 3]>> = date_sources_by_name
        .into_iter()
        .map(|(name, dss)| {
            (
                name.clone(),
                dss.iter()
                    .map(|ds| {
                        let [y, m, d] = ymd_indices_by_name.get(&name).unwrap();
                        [ds[*y], ds[*m], ds[*d]]
                    })
                    .collect::<Vec<_>>(),
            )
        })
        .collect();

    let result = dates_by_name
        .into_iter()
        .filter(|(_, ds)| ds.iter().any(|d| *d == [1, 9, 11]))
        .map(|(name, _)| name)
        .collect::<Vec<_>>()
        .join(" ");

    println!("{}", result);
}
