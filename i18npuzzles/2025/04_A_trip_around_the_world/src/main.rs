use std::io::{self, BufRead};

use chrono::{DateTime, NaiveDateTime, TimeZone};
use chrono_tz::Tz;
use regex::Regex;

fn line_parts(s: &str) -> (String, String) {
    let re = Regex::new(r"^(Arrival|Departure):\s+([A-Za-z_\-/]+)\s+(.+)$").unwrap();
    let caps = re.captures(s).unwrap();
    (caps[2].to_string(), caps[3].to_string())
}

fn parse_naive_date_time(s: &str) -> NaiveDateTime {
    NaiveDateTime::parse_from_str(s, "%b %d, %Y, %H:%M").unwrap()
}

fn date_time_for(timezone_name: &str, ndt: &NaiveDateTime) -> DateTime<Tz> {
    let tz: Tz = timezone_name.parse().unwrap();
    tz.from_local_datetime(ndt).unwrap()
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap())
        .filter(|s| !s.is_empty())
        .collect();

    let dts: Vec<DateTime<Tz>> = lines
        .into_iter()
        .map(|s| {
            let (a, b) = line_parts(&s);
            date_time_for(&a, &parse_naive_date_time(&b))
        })
        .collect();

    let duration_minutes: Vec<i64> = dts
        .chunks(2)
        .map(|ab| ab[1].signed_duration_since(ab[0]).num_minutes())
        .collect();

    let result: i64 = duration_minutes.into_iter().sum();

    println!("{}", result);
}

#[cfg(test)]
mod tests {
    use chrono::{DateTime, TimeZone, Utc};

    use super::*;

    #[test]
    fn parse_naive_date_time_works() {
        let a = parse_naive_date_time("Mar 06, 2020, 16:09");
        let b = Utc.from_utc_datetime(&a);
        let c = DateTime::parse_from_rfc3339("2020-03-06T16:09:00+00:00").unwrap();
        assert_eq!(b.timestamp(), c.timestamp());
    }

    #[test]
    fn line_parts_works_1() {
        assert_eq!(
            line_parts("Departure: Europe/London                  Mar 04, 2020, 10:00"),
            ("Europe/London".to_owned(), "Mar 04, 2020, 10:00".to_owned())
        );
    }

    #[test]
    fn line_parts_works_2() {
        assert_eq!(
            line_parts("Arrival:   America/Argentina/Buenos_Aires Mar 06, 2020, 19:10"),
            (
                "America/Argentina/Buenos_Aires".to_owned(),
                "Mar 06, 2020, 19:10".to_owned()
            )
        );
    }
}
