enum Mode {
    Content,
    Garbage,
}

struct StepResult {
    i_delta: usize,
    result_delta: i32,
    mode: Mode,
    level: i32,
}

fn content_step(level: i32, x: char) -> StepResult {
    match x {
        '{' => StepResult {
            i_delta: 1,
            result_delta: 0,
            mode: Mode::Content,
            level: level + 1,
        },
        '}' => StepResult {
            i_delta: 1,
            result_delta: level,
            mode: Mode::Content,
            level: level - 1,
        },
        '<' => StepResult {
            i_delta: 1,
            result_delta: 0,
            mode: Mode::Garbage,
            level,
        },
        _ => StepResult {
            i_delta: 1,
            result_delta: 0,
            mode: Mode::Content,
            level,
        },
    }
}

fn garbage_step(level: i32, x: char) -> StepResult {
    match x {
        '!' => StepResult {
            i_delta: 2,
            result_delta: 0,
            mode: Mode::Garbage,
            level,
        },
        '>' => StepResult {
            i_delta: 1,
            result_delta: 0,
            mode: Mode::Content,
            level,
        },
        _ => StepResult {
            i_delta: 1,
            result_delta: 0,
            mode: Mode::Garbage,
            level,
        },
    }
}

fn main() {
    let xs: Vec<char> = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .chars()
        .collect();

    let mut result: i32 = 0;
    let mut level: i32 = 0;
    let mut i: usize = 0;
    let mut mode: Mode = Mode::Content;

    while i < xs.len() {
        let r = match mode {
            Mode::Content => content_step(level, xs[i]),
            Mode::Garbage => garbage_step(level, xs[i]),
        };

        i += r.i_delta;
        result += r.result_delta;
        mode = r.mode;
        level = r.level;
    }

    println!("{}", result);
}
