# Usage

Given the puzzle input file is `in1`,

```
$ ./multi_tzdb_local_time_to_utc.clj < in1
...
$ ./solve.clj < in1
```

The `multi_tzdb_local_time_to_utc` script automates the preparation of 4 different versions of TZDATA used to parse the puzzle input. It produces 4 output text files with UTC times -- one per each TZDATA version.

The `solve` script needs the 4 UTC files and the original input file in order to find the [puzzle](https://i18n-puzzles.com/puzzle/19/) answer.
