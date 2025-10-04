use ac_library::FenwickTree;
use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        q: usize,
        xy: [(usize, usize); q],
    }

    let mut ft: FenwickTree<usize> = FenwickTree::new(n + 1, 0);
    for i in 1..=n {
        ft.add(i, 1);
    }

    let mut lo: usize = 0;

    for (highest_upgraded_version, new_version) in xy {
        assert!(new_version > highest_upgraded_version);

        if highest_upgraded_version < lo {
            writeln!(writer, "0").unwrap();
        } else {
            let upgraded_count = ft.sum(lo..=highest_upgraded_version);
            lo = highest_upgraded_version + 1;
            ft.add(new_version, upgraded_count);
            writeln!(writer, "{upgraded_count}").unwrap();
        }
    }

    writer.flush().unwrap();
}
