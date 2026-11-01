use itertools::Itertools;
use std::{
    collections::HashMap,
    io::{BufRead, stdin},
};

#[derive(Clone, Copy, Debug)]
struct Record {
    id: i32,
    quest: i32,
    part: i32,
    time: i32,
}

fn decode_prefixed_number(s: &str, prefix: &str) -> i32 {
    s.strip_prefix(prefix).unwrap().parse().unwrap()
}

fn decode_record(s: String) -> Record {
    let (id_source, quest_source, part_source, time_source) = s.split(' ').collect_tuple().unwrap();
    let id = decode_prefixed_number(id_source, "id=");
    let quest = decode_prefixed_number(quest_source, "quest=");
    let part = decode_prefixed_number(part_source, "part=");
    assert!(matches!(part, 1..=3));
    let time = decode_prefixed_number(time_source, "time=");

    Record {
        id,
        quest,
        part,
        time,
    }
}

fn points_by_id(max_points: i32, mut ids_and_times: Vec<(i32, i32)>) -> HashMap<i32, i32> {
    let ps: Vec<i32> = (1..=max_points).rev().collect();
    ids_and_times.sort_by_key(|&(_, time)| time);

    ps.into_iter()
        .zip(ids_and_times)
        .map(|(p, (id, _))| (id, p))
        .collect()
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let records: Vec<_> = lines.into_iter().map(decode_record).collect();
    let max_id = records.iter().map(|r| r.id).max().unwrap();
    let max_quest = records.iter().map(|r| r.quest).max().unwrap();

    let mut total_points: Vec<i32> = (1..=max_quest).cartesian_product(1..=3).fold(
        vec![0; max_id as usize],
        |mut agg, (quest, part)| {
            let mut ids_and_times: Vec<(i32, i32)> = records
                .iter()
                .filter_map(|r| {
                    (r.quest == quest
                        && r.part <= part
                        && records
                            .iter()
                            .any(|rr| rr.id == r.id && rr.quest == quest && rr.part == part))
                    .then_some((r.id, r.time))
                })
                .collect();
            ids_and_times.sort();

            ids_and_times.dedup_by(|cur, prev| {
                if cur.0 == prev.0 {
                    prev.1 += cur.1;
                    true
                } else {
                    false
                }
            });

            eprintln!("quest:{quest} part:{part} ids_and_times:{ids_and_times:?}");

            for (id, p) in points_by_id(part * 50, ids_and_times) {
                agg[(id - 1) as usize] += p;
            }

            agg
        },
    );

    total_points.sort_by(|a, b| b.cmp(a));
    eprintln!("{total_points:?}");

    let result: i32 = total_points
        .into_iter()
        .enumerate()
        .map(|(i, p)| ((i + 1) as i32) * p)
        .sum();

    println!("{result}");
}
