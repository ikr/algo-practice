use proconio::input;
use proconio::marker::Bytes;
use std::fmt::{Display, Formatter, Result};
use std::io::{BufWriter, Write, stdout};

#[derive(Clone, Copy)]
enum Kind {
    Takahashi,
    Aoki,
    Unknown,
}

impl Display for Kind {
    fn fmt(&self, f: &mut Formatter<'_>) -> Result {
        let name = match self {
            Self::Takahashi => "Takahashi",
            Self::Aoki => "Aoki",
            Self::Unknown => "Unknown",
        };
        f.write_str(name)
    }
}

fn is_word_in_alphabet(word: &[u8], alphabet: &[u8]) -> bool {
    word.iter().all(|x| alphabet.contains(x))
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        _: usize,
        _: usize,
        takahashi_alphabet: Bytes,
        aoki_alphabet: Bytes,
        t: usize,
        words: [Bytes; t],
    }

    for w in words {
        let ta = is_word_in_alphabet(&w, &takahashi_alphabet);
        let ao = is_word_in_alphabet(&w, &aoki_alphabet);

        let result = if ta && !ao {
            Kind::Takahashi
        } else if ao && !ta {
            Kind::Aoki
        } else {
            Kind::Unknown
        };
        writeln!(writer, "{}", result).unwrap();
    }

    writer.flush().unwrap();
}
