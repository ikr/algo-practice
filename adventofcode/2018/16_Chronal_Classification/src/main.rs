fn read_input_parts() -> (String, String) {
    match std::io::read_to_string(std::io::stdin()) {
        Ok(s) => {
            let parts = s.split("\n\n\n").collect::<Vec<&str>>();
            (parts[0].to_string(), parts[1].to_string())
        }
        Err(e) => panic!("Error reading from stdin: {}", e),
    }
}

fn split_samples(s: &str) -> Vec<String> {
    s.split("\n\n").map(|s| s.to_string()).collect()
}

type Val = u32;
type Regs = [Val; 4];
type Args = [Val; 3];
type Opcode = u8;

enum Op {
    Addr,
    Addi,
    Mulr,
    Muli,
    Banr,
    Bani,
    Borr,
    Bori,
    Setr,
    Seti,
    Gtir,
    Gtri,
    Gtrr,
    Eqir,
    Eqri,
    Eqrr,
}

fn main() {
    let (samples_source, _) = read_input_parts();
    let sample_sources = split_samples(&samples_source);
    eprintln!("{:?}", sample_sources);
}
