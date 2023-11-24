use regex::Regex;
use std::collections::HashMap;
use std::io::{self, BufRead};

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

#[derive(PartialEq)]
enum State {
    Awake,
    Asleep,
}

fn read_input() -> Vec<String> {
    let mut xs = Vec::new();
    for line in io::stdin().lock().lines() {
        xs.push(String::from(line.unwrap().trim()));
    }
    xs.sort();
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

fn minute_id(h: u8, m: u8) -> usize {
    if h == 0 {
        (m + 60) as usize
    } else {
        assert!(h == 23);
        m as usize
    }
}

fn main() {
    let entries = read_input()
        .iter()
        .map(|x| parse_log_entry(x))
        .collect::<Vec<_>>();

    let mut sleep_minutes_by_guard_id: HashMap<u16, [u16; 120]> = HashMap::new();
    let mut current_guard_id: u16 = 0;
    let mut current_minute_id: usize = 0;
    let mut current_state: State = State::Awake;

    for e in entries {
        match e.event {
            Event::BeginShift { guard_id } => {
                assert!(current_state == State::Awake);

                current_guard_id = guard_id;
                current_minute_id = minute_id(e.hour, e.minute);
                current_state = State::Awake;

                sleep_minutes_by_guard_id
                    .entry(current_guard_id)
                    .or_insert([0; 120]);
            }

            Event::FallAsleep => {
                current_minute_id = minute_id(e.hour, e.minute);
                current_state = State::Asleep;
            }

            Event::WakeUp => {
                if current_state == State::Asleep {
                    assert!(current_minute_id < minute_id(e.hour, e.minute));

                    for i in current_minute_id..minute_id(e.hour, e.minute) {
                        sleep_minutes_by_guard_id
                            .get_mut(&current_guard_id)
                            .unwrap()[i] += 1;
                    }
                }

                current_minute_id = minute_id(e.hour, e.minute);
                current_state = State::Awake;
            }
        }
    }

    let mut hi_id = 0;
    let mut hi = 0;

    for (id, &xs) in &sleep_minutes_by_guard_id {
        let s = xs.iter().fold(0, |a, &b| a + b);

        if s > hi {
            hi_id = *id;
            hi = s;
        }
    }

    let xs = sleep_minutes_by_guard_id.get(&hi_id).unwrap();
    let m = xs.iter().max().unwrap();
    let i = xs.iter().position(|&x| x == *m).unwrap();
    println!("{}", usize::from(hi_id) * usize::from(i - 60));
}
