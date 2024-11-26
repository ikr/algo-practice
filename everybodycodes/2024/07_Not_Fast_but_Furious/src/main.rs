use std::io::{self, BufRead};

fn parse_line(s: &str) -> (String, Vec<i32>) {
    let parts: Vec<&str> = s.split(":").collect();
    let lhs = parts[0].to_string();
    let rhs = parts[1]
        .split(",")
        .map(|s| match s {
            "-" => -1,
            "=" => 0,
            "+" => 1,
            _ => panic!("Unknown op {}", s),
        })
        .collect();
    (lhs, rhs)
}

fn total_essence_gathered(track: &[i32], loops: usize, initial_essence: i32, xs: &[i32]) -> i32 {
    let mut t: usize = 0;
    let mut cur = initial_essence;
    let mut result = 0;
    let m = xs.len();

    for _ in 0..loops {
        for terrain in track {
            match (terrain, xs[t % m]) {
                (-1, _) => cur -= 1,
                (0, x) => cur += x,
                (1, _) => cur += 1,
                _ => panic!("Unknown terrain {} or op {}", terrain, xs[t % m]),
            }
            result += cur;
            t += 1;
        }
    }

    result
}

fn track_src() -> String {
    "S+= +=-== +=++=     =+=+=--=    =-= ++=     +=-  =+=++=-+==+ =++=-=-=--
- + +   + =   =     =      =   == = - -     - =  =         =-=        -
= + + +-- =-= ==-==-= --++ +  == == = +     - =  =    ==++=    =++=-=++
+ + + =     +         =  + + == == ++ =     = =  ==   =   = =++=       \n\
= = + + +== +==     =++ == =+=  =  +  +==-=++ =   =++ --= + =          \n\
+ ==- = + =   = =+= =   =       ++--          +     =   = = =--= ==++==
=     ==- ==+-- = = = ++= +=--      ==+ ==--= +--+=-= ==- ==   =+=    =
-               = = = =   +  +  ==+ = = +   =        ++    =          -
-               = + + =   +  -  = + = = +   =        +     =          -
--==++++==+=+++-= =-= =-+-=  =+-= =-= =--   +=++=+++==     -=+=++==+++-"
        .to_string()
}

fn track_from(src: &str) -> Vec<i32> {
    let lines = src.split("\n").collect::<Vec<_>>();
    let grid: Vec<Vec<u8>> = lines.iter().map(|line| line.as_bytes().to_vec()).collect();

    let neigh = |pre: (usize, usize), crd: (usize, usize)| -> (usize, usize) {
        let (ro, co) = crd;
        let h = grid.len();
        let w = grid[ro].len();

        if ro != 0 && (ro - 1, co) != pre && grid[ro - 1][co] != b' ' {
            return (ro - 1, co);
        }

        if ro != h - 1 && (ro + 1, co) != pre && grid[ro + 1][co] != b' ' {
            return (ro + 1, co);
        }

        if co != 0 && (ro, co - 1) != pre && grid[ro][co - 1] != b' ' {
            return (ro, co - 1);
        }

        if co != w - 1 && (ro, co + 1) != pre && grid[ro][co + 1] != b' ' {
            return (ro, co + 1);
        }

        panic!("No neighbour found")
    };

    let mut result = vec![1];
    let mut pre: (usize, usize) = (0, 0);
    let mut cur: (usize, usize) = (0, 1);

    loop {
        let (ro, co) = neigh(pre, cur);

        match grid[ro][co] {
            b'=' => result.push(0),
            b'S' => result.push(0),
            b'+' => result.push(1),
            b'-' => result.push(-1),
            _ => panic!("Unexpected terrain `{}`", grid[ro][co]),
        }

        if grid[ro][co] == b'S' {
            break;
        }

        pre = cur;
        cur = (ro, co);
    }

    result
}

fn main() {
    let mut lines = io::stdin()
        .lock()
        .lines()
        .map(|line| parse_line(&line.unwrap()))
        .collect::<Vec<_>>();

    eprintln!("{:?}", track_from(&track_src()));
}
