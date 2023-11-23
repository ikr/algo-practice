use regex::Regex;
use std::collections::HashMap;
use std::io::{self, BufRead};

// Be sure to sort the input lines:
// $ cat ./in1 | sort | ./target/debug/solution

#[derive(Debug)]
struct LogEntry {
    hour: u8,
    minute: u8,
    event: Event,
}

#[derive(Debug)]
enum Event {
    BeginShift { guard_id: u16 },
    FallAsleep,
    WakeUp,
}

enum State {
    Awake,
    Asleep,
}

fn read_input() -> Vec<String> {
    let mut xs = Vec::new();
    for line in io::stdin().lock().lines() {
        xs.push(String::from(line.unwrap().trim()));
    }
    xs
}

fn parse_log_entry(src: &str) -> LogEntry {
    let re = Regex::new(r"^\[\d{4}-\d{2}-\d{2} (\d{2}):(\d{2})\] (.+)$").unwrap();
    let caps = re.captures(src).unwrap();

    LogEntry {
        hour: caps[1].parse().unwrap(),
        minute: caps[2].parse().unwrap(),
        event: parse_event(&caps[3]),
    }
}

fn parse_event(src: &str) -> Event {
    if src == "falls asleep" {
        Event::FallAsleep
    } else if src == "wakes up" {
        Event::WakeUp
    } else {
        parse_begin_shift(src)
    }
}

fn parse_begin_shift(src: &str) -> Event {
    let re = Regex::new(r"^Guard #(\d+) begins shift$").unwrap();
    let caps = re.captures(src).unwrap();

    Event::BeginShift {
        guard_id: caps[1].parse().unwrap(),
    }
}

fn main() {
    let entries = read_input()
        .iter()
        .map(|x| parse_log_entry(x))
        .collect::<Vec<_>>();

    let mut sleep_minutes_by_guard_id: HashMap<u16, [u8; 120]> = HashMap::new();
    let mut current_guard_id: u16 = 0;
    let mut current_minute: u8 = 0;
    let mut current_state: State = State::Awake;

    for e in entries {
        match e.event {
            Event::BeginShift { guard_id } => {
                current_guard_id = guard_id;
                current_minute = e.minute;
                current_state = State::Awake;

                sleep_minutes_by_guard_id
                    .entry(current_guard_id)
                    .or_insert([0; 120]);
            }
            Event::FallAsleep => {
                // todo
            }
            Event::WakeUp => {
                // todo
            }
        }
    }
}
