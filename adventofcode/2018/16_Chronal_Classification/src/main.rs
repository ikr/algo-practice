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
type AbstractInstruction = (Opcode, Args);

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

#[derive(Debug)]
struct Sample {
    before: Regs,
    instruction: AbstractInstruction,
    after: Regs,
}

impl Sample {
    fn parse(s: &str) -> Sample {
        let lines = s.split("\n").collect::<Vec<&str>>();
        let abstract_instruction_quad = parse_quad(" ", &lines[1]);
        Sample {
            before: parse_quad(", ", &Sample::infix(lines[0])),
            instruction: (
                abstract_instruction_quad[0] as u8,
                [
                    abstract_instruction_quad[1],
                    abstract_instruction_quad[2],
                    abstract_instruction_quad[3],
                ],
            ),
            after: parse_quad(", ", &Sample::infix(lines[2])),
        }
    }

    fn infix(s: &str) -> String {
        let prefix_length = "Before: [".len();
        s[prefix_length..s.len() - 1].to_string()
    }
}

fn parse_quad(sep: &str, src: &str) -> [Val; 4] {
    src.split(sep)
        .map(|s| s.parse::<Val>().unwrap())
        .collect::<Vec<Val>>()
        .try_into()
        .unwrap()
}

fn main() {
    let (samples_source, _) = read_input_parts();
    let sample_sources = split_samples(&samples_source);
    eprintln!("{:?}", sample_sources);
}
