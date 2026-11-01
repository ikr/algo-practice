use itertools::Itertools;
use std::io::{BufRead, stdin};

#[derive(Clone, Copy, Debug)]
struct Record {
    id: i32,
    _quest: i32,
    _part: i32,
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
    let time = decode_prefixed_number(time_source, "time=");

    Record {
        id,
        _quest: quest,
        _part: part,
        time,
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let records: Vec<_> = lines.into_iter().map(decode_record).collect();
    let max_id = records.iter().map(|r| r.id).max().unwrap();

    let mut total_times_by_index: Vec<i32> =
        records
            .into_iter()
            .fold(vec![0; max_id as usize], |mut agg, r| {
                agg[r.id as usize - 1] += r.time;
                agg
            });

    total_times_by_index.sort();

    let result: i32 = total_times_by_index
        .into_iter()
        .enumerate()
        .map(|(i, tt)| ((i + 1) as i32) * tt)
        .sum();

    println!("{result}");
}
