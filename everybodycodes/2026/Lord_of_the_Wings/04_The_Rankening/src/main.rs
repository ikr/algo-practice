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
    let record_ids: Vec<_> = records.iter().map(|r| r.id).collect();
    let fqs_by_id = record_ids.into_iter().counts();

    let max_id = records.iter().map(|r| r.id).max().unwrap();

    let mut ids_and_total_times: Vec<(i32, i32)> = records.into_iter().fold(
        (1..=max_id).map(|id| (id, 0)).collect::<Vec<_>>(),
        |mut agg, r| {
            let i = (r.id - 1) as usize;
            let (_, tt) = agg[i];
            agg[i] = (r.id, tt + r.time);
            agg
        },
    );

    ids_and_total_times.sort_by_key(|&(id, tt)| {
        let fq: i32 = *fqs_by_id.get(&id).unwrap() as i32;
        (-fq, tt)
    });

    let result: i32 = ids_and_total_times
        .into_iter()
        .enumerate()
        .map(|(i, (_, tt))| ((i + 1) as i32) * tt)
        .sum();

    println!("{result}");
}
