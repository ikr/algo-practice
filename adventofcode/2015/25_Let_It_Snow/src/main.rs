const FIRST_CODE: u64 = 20151125;

fn end_coord() -> (u16, u16) {
    (2981, 3075)
}

fn next_code(x: u64) -> u64 {
    (x * 252533) % 33554393
}

fn next_coord(coord: (u16, u16)) -> (u16, u16) {
    let (r, c) = coord;
    if r - 1 == 0 {
        (c + 1, 1)
    } else {
        (r - 1, c + 1)
    }
}

fn main() {
    let mut coord: (u16, u16) = (1, 1);
    let mut code: u64 = FIRST_CODE;
    loop {
        coord = next_coord(coord);
        code = next_code(code);
        if coord == end_coord() {
            break;
        }
    }
    println!("{}", code);
}
