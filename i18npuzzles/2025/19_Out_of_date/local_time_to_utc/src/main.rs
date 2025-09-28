use chrono::{DateTime, NaiveDateTime, TimeZone, Utc};
use chrono_tz::Tz;
use std::io::{BufRead, stdin};

fn parse_line(src: String) -> DateTime<Tz> {
    let parts: Vec<_> = src.split("; ").collect();
    let ndt = NaiveDateTime::parse_from_str(parts[0], "%Y-%m-%d %H:%M:%S").unwrap();
    let tz: Tz = parts[1].parse().unwrap();
    tz.from_local_datetime(&ndt).unwrap()
}

fn format_utc(dt: DateTime<Tz>) -> String {
    let utc_dt = dt.with_timezone(&Utc);
    let formatted = utc_dt.to_rfc3339_opts(chrono::SecondsFormat::Secs, false);
    format!("{formatted}")
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let result: Vec<String> = lines.into_iter().map(parse_line).map(format_utc).collect();
    println!("{}", result.join("\n"));
}
