use std::{
    collections::BTreeMap,
    io::{self, BufRead},
};

#[derive(Debug, Clone, Copy)]
enum OpCode {
    And,
    Or,
    Xor,
}

impl OpCode {
    fn parse(s: &str) -> Self {
        match s {
            "AND" => Self::And,
            "OR" => Self::Or,
            "XOR" => Self::Xor,
            _ => panic!("Invalid opcode `{}`", s),
        }
    }
}

#[derive(Debug, Clone)]
struct Gate {
    opcode: OpCode,
    lhs_id: String,
    rhs_id: String,
    out_id: String,
}

impl Gate {
    fn parse_op(s: &str) -> (OpCode, String, String) {
        let parts = s.split_whitespace().collect::<Vec<_>>();
        (
            OpCode::parse(parts[1]),
            parts[0].to_string(),
            parts[2].to_string(),
        )
    }

    fn parse(s: &str) -> Gate {
        let parts = s.split(" -> ").collect::<Vec<_>>();
        let (opcode, lhs_id, rhs_id) = Gate::parse_op(parts[0]);
        let out_id = parts[1].to_string();
        Gate {
            opcode,
            lhs_id,
            rhs_id,
            out_id,
        }
    }
}

fn parse_input(s: &str) -> (String, u8) {
    let parts = s.split(": ").collect::<Vec<_>>();
    (parts[0].to_string(), parts[1].parse().unwrap())
}

struct Machine {
    values: BTreeMap<String, u8>,
    gates_by_input: BTreeMap<String, Vec<Gate>>,
}

impl Machine {
    fn propagate(&mut self, id: &str) {
        let mut ids_to_propagate: Vec<String> = vec![];

        if let Some(gates) = self.gates_by_input.get(id) {
            for gate in gates.iter() {
                if let Some(lhs) = self.values.get(&gate.lhs_id) {
                    if let Some(rhs) = self.values.get(&gate.rhs_id) {
                        let value = match gate.opcode {
                            OpCode::And => lhs & rhs,
                            OpCode::Or => lhs | rhs,
                            OpCode::Xor => lhs ^ rhs,
                        };

                        self.values.insert(gate.out_id.clone(), value);
                        ids_to_propagate.push(gate.out_id.clone());
                    }
                }
            }
        }

        for id in ids_to_propagate {
            self.propagate(&id);
        }
    }

    fn gather_value(&self, prefix: char) -> usize {
        let mut result = 0;
        for i in 0..63 {
            let id: String = format!("{}{:02}", prefix, i);
            if let Some(value) = self.values.get(&id) {
                let x = (*value as usize) << i;
                result |= x;
            }
        }
        result
    }
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().to_string())
        .collect();

    let isep = lines.iter().position(|s| s.is_empty()).unwrap();
    let values: BTreeMap<String, u8> = lines[0..isep].iter().map(|s| parse_input(&s)).collect();
    let gates: Vec<Gate> = lines[isep + 1..].iter().map(|s| Gate::parse(&s)).collect();
    let input_ids: Vec<String> = values.keys().cloned().collect();

    let gates_by_input: BTreeMap<String, Vec<Gate>> =
        gates.iter().fold(BTreeMap::new(), |mut acc, gate| {
            acc.entry(gate.lhs_id.clone())
                .or_insert_with(Vec::new)
                .push(gate.clone());
            acc
        });

    let mut m = Machine {
        values,
        gates_by_input,
    };

    for _ in 0..100 {
        for id in input_ids.iter() {
            m.propagate(&id);
        }
    }

    println!("{}", m.gather_value('z'));
}
