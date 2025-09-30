# About

Reads the lines of the following format from the STDIN:

```
2024-04-09 18:49:00; Africa/Casablanca
2024-04-10 02:19:00; Asia/Pyongyang
2024-04-10 04:49:00; Antarctica/Casey
...
```

Each line defines a local time in a specific time zone. This program converts the given local times into UTC times, using a pinned version of the [IANA tzdata](https://github.com/eggert/tz) within a local copy of the [chrono-tz library.](https://github.com/chronotope/chrono-tz)

Outputs the corresponding lines of ISO-8601-formatted UTC times, like:

```
2024-04-09T18:49:00+00:00
2024-04-09T17:19:00+00:00
2024-04-09T17:49:00+00:00
...
```

The `case-insensitive` feature bit in the `Cargo.toml` is very important:

```toml
[dependencies]
chrono-tz = { path = "../chrono-tz/chrono-tz", features = ["case-insensitive"] }
```

It forces the local instance of chrono-tz/chrono-tz to use the IANA TZDB files in the `chrono-tz/chrono-tz/tz` directory, instead of the pre-built TZDATA in the `chrono-tz/chrono-tz/src/prebuilt`.
