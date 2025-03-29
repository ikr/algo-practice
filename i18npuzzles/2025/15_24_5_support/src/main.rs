use chrono::{DateTime, Duration, NaiveDate, NaiveTime, TimeZone, Utc};
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
        .map(|day| {
            let start = tz
                .from_local_datetime(&day.and_time(local_start_time))
                .unwrap()
                .with_timezone(&Utc);
            let end = tz
                .from_local_datetime(&day.and_time(local_end_time))
                .unwrap()
                .with_timezone(&Utc);
            (start, end)
        })
        .collect()
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

    let local_day = (
        NaiveTime::from_hms_opt(0, 00, 0).unwrap(),
        NaiveTime::from_hms_milli_opt(23, 59, 59, 999).unwrap(),
    );

    let office_intervals: Vec<(DateTime<Utc>, DateTime<Utc>)> = offices
        .into_iter()
        .flat_map(|(_, tz, holidays)| daily_intervals(tz, &holidays, local_work_day))
        .collect();

    // let client_intervals: Vec<(DateTime<Utc>, DateTime<Utc>)> = clients
    //     .into_iter()
    //     .flat_map(|(_, tz, holidays)| daily_intervals(tz, &holidays, local_day))
    //     .collect();

    eprintln!("{}", office_intervals.len());
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
