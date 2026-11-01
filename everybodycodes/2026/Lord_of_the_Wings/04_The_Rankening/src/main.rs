use itertools::Itertools;
use std::io::{BufRead, stdin};

#[derive(Clone, Copy, Debug)]
struct Record {
    id: usize,
    quest: usize,
    part: usize,
    time: usize,
}

fn decode_prefixed_number(s: &str, prefix: &str) -> usize {
    s.strip_prefix(prefix).unwrap().parse().unwrap()
}

fn decode_record(s: String) -> Record {
    let (id_source, quest_source, part_source, time_source) = s.split(' ').collect_tuple().unwrap();
    let id = decode_prefixed_number(id_source, "id=") - 1;
    let quest = decode_prefixed_number(quest_source, "quest=") - 1;
    let part = decode_prefixed_number(part_source, "part=") - 1;
    let time = decode_prefixed_number(time_source, "time=");

    Record {
        id,
        quest,
        part,
        time,
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let records: Vec<_> = lines.into_iter().map(decode_record).collect();
    eprintln!("{records:?}");
}
