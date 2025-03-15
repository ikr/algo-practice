use std::io::{self, BufRead};

use chrono::{Duration, Timelike};
use chrono::{NaiveDateTime, TimeZone};
use chrono_tz::America::{Halifax, Santiago};
use chrono_tz::GMT;

#[derive(Debug, Copy, Clone, PartialEq)]
struct SourceDateTime {
    naive_date_time: NaiveDateTime,
    gmt_offset_hours: i64,
}

impl SourceDateTime {
    fn parse(s: &str) -> Self {
        let n = s.len();
        let suff_len = "-04:00".len();

        let naive_date_time: NaiveDateTime = s[..n - suff_len].parse().unwrap();
        let gmt_offset_hours = -s[n - suff_len + 2..]
            .chars()
            .next()
            .map(|c| c.to_digit(10).unwrap() as i64)
            .unwrap();

        Self {
            naive_date_time,
            gmt_offset_hours,
        }
    }
}

fn parse_line(s: &str) -> (SourceDateTime, i64, i64) {
    let parts: Vec<_> = s.split_whitespace().collect();
    (
        SourceDateTime::parse(parts[0]),
        parts[1].parse().unwrap(),
        parts[2].parse().unwrap(),
    )
}

fn main() {
    let lines: Vec<_> = io::stdin()
        .lock()
        .lines()
        .map(|s| parse_line(&s.unwrap()))
        .collect();

    let corrected: Vec<_> = lines
        .into_iter()
        .map(|(sdt, correct_duration_minutes, wrong_duration_munutes)| {
            let gmt = GMT.from_local_datetime(&sdt.naive_date_time).unwrap()
                - Duration::hours(sdt.gmt_offset_hours);
            let in_halifax = Halifax.from_local_datetime(&sdt.naive_date_time).unwrap();
            let in_santiago = Santiago.from_local_datetime(&sdt.naive_date_time).unwrap();

            let a = if gmt.timestamp() == in_halifax.timestamp() {
                in_halifax
            } else {
                in_santiago
            };
            (a, correct_duration_minutes, wrong_duration_munutes)
        })
        .collect();

    let result: usize = corrected
        .into_iter()
        .map(|(dt0, correct_duration_minutes, wrong_duration_munutes)| {
            let dt = dt0 - Duration::minutes(wrong_duration_munutes)
                + Duration::minutes(correct_duration_minutes);
            dt.hour() as usize
        })
        .enumerate()
        .map(|(i, h)| (i + 1) * h)
        .sum();
    println!("{}", result)
}

#[cfg(test)]
mod tests {
    use chrono::{NaiveDate, NaiveTime};

    use super::*;

    #[test]
    fn source_date_time_parse_works() {
        assert_eq!(
            SourceDateTime::parse("2012-11-05T09:39:00.000-04:00"),
            SourceDateTime {
                naive_date_time: NaiveDateTime::new(
                    NaiveDate::from_ymd_opt(2012, 11, 05).unwrap(),
                    NaiveTime::from_hms_opt(9, 39, 0).unwrap()
                ),
                gmt_offset_hours: -4,
            }
        )
    }
}
