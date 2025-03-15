use std::io::{self, BufRead};

use chrono::NaiveDateTime;

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

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap())
        .collect();

    eprintln!("{:?}", lines);
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
