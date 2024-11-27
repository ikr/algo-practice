use std::io::{self, Read};

fn main() {
    let mut buf = String::new();
    io::stdin().read_to_string(&mut buf).unwrap();
    let num_priests: i64 = buf.trim().parse().unwrap();
    let num_acolytes: i64 = 10;
    //let num_acolytes: i64 = 5;
    let initially_available_blocks: i64 = 202400000;
    //let initially_available_blocks: i64 = 160;

    let fill_next_layer = |mut xs: Vec<i64>| -> Vec<i64> {
        let thickness = xs.last().unwrap();
        let new_thickness = ((thickness * num_priests) % num_acolytes) + num_acolytes;

        for x in xs.iter_mut() {
            *x += new_thickness;
        }
        xs.push(new_thickness);
        xs
    };

    let width = |xs: &[i64]| -> i64 {
        let n: i64 = xs.len() as i64;
        n + n - 1
    };

    let num_blocks = |xs: &[i64]| -> i64 { 2 * xs[1..].iter().sum::<i64>() + xs[0] };

    let carve_out_empty_spaces = |xs: &[i64]| -> Vec<i64> {
        let n = xs.len();
        let w = width(xs);
        let mut result: Vec<i64> = xs.to_vec();

        for i in 0..(n - 1) {
            let current_thickness = xs[i] - xs[i + 1];
            let e = (num_priests * w * xs[i]) % num_acolytes;
            result[i] = current_thickness.max(xs[i] - e);
        }

        result
    };

    let mut xs: Vec<i64> = vec![1];

    loop {
        xs = fill_next_layer(xs);
        let ys = carve_out_empty_spaces(&xs);

        if num_blocks(&ys) >= initially_available_blocks {
            println!("{}", num_blocks(&ys));
            break;
        }
    }
}
