use std::io::{BufWriter, Write, stdin, stdout};

#[derive(Default)]
struct Scanner {
    buffer: Vec<String>,
}

impl Scanner {
    fn next<T: std::str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buffer.pop() {
                return token.parse().ok().expect("Failed parse");
            }
            let mut input = String::new();
            stdin().read_line(&mut input).expect("Failed read");
            self.buffer = input.split_whitespace().rev().map(String::from).collect();
        }
    }
}

fn prefix_freqs(xs: &[usize]) -> Vec<Vec<usize>> {
    xs.iter().fold(Vec::with_capacity(xs.len()), |mut acc, &i| {
        let mut fq: Vec<usize> = if let Some(fq0) = acc.last() {
            fq0.clone()
        } else {
            vec![0; 26]
        };
        fq[i] += 1;
        acc.push(fq);
        acc
    })
}

fn abc_exist(mut xs: Vec<usize>) -> bool {
    let n = xs.len();
    let ltr = prefix_freqs(&xs);
    xs.reverse();
    let rtl = prefix_freqs(&xs);
    xs.reverse();

    for i in 1..n - 1 {
        if ltr[i - 1][xs[i]] != 0 || rtl[n - i - 2][xs[i]] != 0 {
            return true;
        }
    }

    false
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let cases_num: u16 = scanner.next();

    for _ in 1..=cases_num {
        let n: usize = scanner.next();
        let s: String = scanner.next();
        let xs: Vec<usize> = s.bytes().map(|x| (x - b'a') as usize).collect();
        assert_eq!(xs.len(), n);

        let result = abc_exist(xs);
        writeln!(writer, "{}", if result { "Yes" } else { "No" }).unwrap();
    }

    writer.flush().unwrap();
}
