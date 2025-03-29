use chrono::{DateTime, Datelike, Duration, NaiveDate, NaiveTime, TimeZone, Utc, Weekday};
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

fn daily_intervals(
    tz: Tz,
    holidays: &[NaiveDate],
    local_time_interval: (NaiveTime, NaiveTime),
) -> Vec<(DateTime<Utc>, DateTime<Utc>)> {
    let (local_start_time, local_end_time) = local_time_interval;
    let fisrt_day = NaiveDate::from_ymd_opt(2022, 1, 1).unwrap();

    (0..365)
        .map(|offset| fisrt_day + chrono::Duration::days(offset))
        .filter(|day| !holidays.contains(day))
        .filter_map(|day| {
            let a = tz
                .from_local_datetime(&day.and_time(local_start_time))
                .unwrap();
            if a.weekday() == Weekday::Sat || a.weekday() == Weekday::Sun {
                None
            } else {
                let b = tz
                    .from_local_datetime(&day.and_time(local_end_time))
                    .unwrap();

                let start = a.with_timezone(&Utc);
                let end = b.with_timezone(&Utc);
                Some((start, end))
            }
        })
        .collect()
}

fn all_work_day_minutes(tz: Tz, holidays: &[NaiveDate]) -> Vec<DateTime<Utc>> {
    let is_holiday = |dt: DateTime<Tz>| holidays.contains(&dt.date_naive());

    let mut cur = tz
        .from_local_datetime(
            &NaiveDate::from_ymd_opt(2022, 1, 1)
                .unwrap()
                .and_hms_opt(0, 0, 0)
                .unwrap(),
        )
        .unwrap();

    let mut result = vec![];

    while cur.year() == 2022 {
        if !(is_holiday(cur) || cur.weekday() == Weekday::Sat || cur.weekday() == Weekday::Sun) {
            result.push(cur.with_timezone(&Utc));
        }
        cur += Duration::minutes(1);
    }

    result
}

fn intersection_duration<Tz: TimeZone>(
    ab: (DateTime<Tz>, DateTime<Tz>),
    cd: (DateTime<Tz>, DateTime<Tz>),
) -> Option<Duration> {
    let (a, b) = ab;
    let (c, d) = cd;
    let i = std::cmp::max(a, c);
    let j = std::cmp::min(b, d);
    if j >= i { Some(j - i) } else { None }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let isep: usize = lines.iter().position(|s| s.is_empty()).unwrap();
    let offices: Vec<_> = lines[..isep].iter().map(|s| decode_line(s)).collect();
    let clients: Vec<_> = lines[isep + 1..].iter().map(|s| decode_line(s)).collect();

    let local_work_day = (
        NaiveTime::from_hms_opt(8, 30, 0).unwrap(),
        NaiveTime::from_hms_opt(17, 00, 0).unwrap(),
    );

    let office_intervals: Vec<(DateTime<Utc>, DateTime<Utc>)> = offices
        .into_iter()
        .flat_map(|(_, tz, holidays)| daily_intervals(tz, &holidays, local_work_day))
        .collect();

    for (name, tz, holidays) in clients {
        let ms = all_work_day_minutes(tz, &holidays)
            .into_iter()
            .filter(|m| !office_intervals.iter().any(|(a, b)| a <= m && m < b))
            .count();
        eprintln!("{} {}: {} minutes", name, tz, ms);
    }
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
