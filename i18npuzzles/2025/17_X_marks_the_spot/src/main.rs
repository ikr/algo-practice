use std::io::{BufRead, stdin};

/*
+------------+------------+-----------+-----------+-----------+-----------+
| First CP   | Last CP    | Byte 1    | Byte 2    | Byte 3    | Byte 4    |
+------------+------------+-----------+-----------+-----------+-----------+
| U+0000     | U+007F     | 0yyyzzzz  |           |           |           |
| U+0080     | U+07FF     | 110xxxyy  | 10yyzzzz  |           |           |
| U+0800     | U+FFFF     | 1110wwww  | 10xxxxyy  | 10yyzzzz  |           |
| U+010000   | U+10FFFF   | 11110uvv  | 10vvwwww  | 10xxxxyy  | 10yyzzzz  |
+------------+------------+-----------+-----------+-----------+-----------+
*/

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let blocks: Vec<Vec<String>> = lines.into_iter().fold(vec![], |mut acc, line| {
        match (acc.last_mut(), line.as_str()) {
            (Some(_), "") => {
                acc.push(vec![]);
                acc
            }
            (None, "") => unreachable!(),
            (None, _) => {
                acc.push(vec![line]);
                acc
            }
            (Some(last), _) => {
                last.push(line);
                acc
            }
        }
    });
}
