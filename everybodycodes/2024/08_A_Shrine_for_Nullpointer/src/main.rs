use std::io::{self, Read};

fn main() {
    let mut buf = String::new();
    io::stdin().read_to_string(&mut buf).unwrap();
    let num_priests: i64 = buf.trim().parse().unwrap();
    let num_acolytes: i64 = 1111;
    //let num_acolytes: i64 = 5;
    let initially_available_blocks: i64 = 20240000;
    //let initially_available_blocks: i64 = 50;

    let mut available_blocks = initially_available_blocks - 1;
    let mut width: i64 = 1;
    let mut thickness: i64 = 1;

    loop {
        let new_thickness = (thickness * num_priests) % num_acolytes;
        let needed_for_new_layer = 2 * new_thickness + width * new_thickness;

        if available_blocks < needed_for_new_layer {
            let result = (width + 2) * (needed_for_new_layer - available_blocks);
            println!("{}", result);
            break;
        }

        available_blocks -= needed_for_new_layer;
        width += 2;
        thickness = new_thickness;
    }
}
