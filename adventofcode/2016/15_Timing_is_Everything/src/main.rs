use ac_library::math;

fn main() {
    {
        let r = [-4 - 1, -1 - 2];
        let m = [5, 2];
        println!("{:?}", math::crt(&r, &m));
    }
    {
        let r = [-1 - 1, 0 - 2, -2 - 3, 0 - 4, 0 - 5, -5 - 6];
        let m = [17, 7, 19, 5, 3, 13];
        println!("{:?}", math::crt(&r, &m));
    }
}
