use std::io::{BufRead, stdin};
use unicode_bidi::BidiInfo;

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    eprintln!("{:?}", lines);

    for text in lines {
        let bidi_info = BidiInfo::new(&text, None);
        let para = &bidi_info.paragraphs[0];
        let line = para.range.clone();
        let display: String = bidi_info.reorder_line(para, line).chars().collect();
        eprintln!("{text} → {display}");
    }
}
