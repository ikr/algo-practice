use chrono::{DateTime, NaiveDate, Utc};
use chrono_tz::Tz;
use std::io::{BufRead, stdin};

fn decode_naive_date(s: &str) -> NaiveDate {
    NaiveDate::parse_from_str(s, "%d %B %Y").unwrap()
}

fn decode_line(s: &str) -> (String, Tz, Vec<NaiveDate>) {
    let ps: Vec<_> = s.split('\t').collect();
    let holidays: Vec<NaiveDate> = ps[2].split(';').map(decode_naive_date).collect();
    (ps[0].to_string(), ps[1].parse().unwrap(), holidays)
}

fn office_coverage_intervals(
    tz: Tz,
    holidays: &[NaiveDate],
) -> Vec<(DateTime<Utc>, DateTime<Utc>)> {
    let fisrt_day = NaiveDate::from_ymd_opt(2022, 1, 1).unwrap();
    (0..365)
        .map(|offset| fisrt_day + chrono::Duration::days(offset))
        .filter(|day| !holidays.contains(day))
        .map(|day| {
            let start = tz.ymd(day.year(), day.month(), day.day()).and_hms(8, 30, 0);
            let end = tz.ymd(day.year(), day.month(), day.day()).and_hms(17, 0, 0);
            (start, end)
        })
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let isep: usize = lines.iter().position(|s| s.is_empty()).unwrap();

    let offices: Vec<_> = lines[..isep].iter().map(|s| decode_line(s)).collect();
    eprintln!("{:?}", offices);

    let clients: Vec<_> = lines[isep + 1..].iter().map(|s| decode_line(s)).collect();
    eprintln!("{:?}", clients);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn decode_naive_date_works() {
        assert_eq!(
            decode_naive_date("6 June 2022"),
            NaiveDate::from_ymd_opt(2022, 6, 6).unwrap()
        );
    }
}
