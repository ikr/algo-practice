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
