use std::{
    collections::BTreeMap,
    io::{self, BufRead},
};

use itertools::Itertools;

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
    input_ids: Vec<String>,
}

impl Machine {
    fn new(values: BTreeMap<String, u8>, gates: &[Gate]) -> Self {
        let input_ids: Vec<String> = values.keys().cloned().collect();

        let gates_by_input: BTreeMap<String, Vec<Gate>> =
            gates.iter().fold(BTreeMap::new(), |mut acc, gate| {
                acc.entry(gate.lhs_id.clone())
                    .or_insert_with(Vec::new)
                    .push(gate.clone());
                acc
            });

        Machine {
            values,
            gates_by_input,
            input_ids,
        }
    }

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

    fn run(&mut self) -> usize {
        for _ in 0..100 {
            for id in self.input_ids.clone().iter() {
                self.propagate(&id);
            }
        }
        gather_value(&self.values, 'z')
    }
}

fn gather_value(values: &BTreeMap<String, u8>, prefix: char) -> usize {
    let mut result = 0;
    for i in 0..63 {
        let id: String = format!("{}{:02}", prefix, i);
        if let Some(value) = values.get(&id) {
            let x = (*value as usize) << i;
            result |= x;
        }
    }
    result
}

fn without(xs: &[usize], a: usize, b: usize) -> Vec<usize> {
    xs.iter().filter(|&&x| x != a && x != b).copied().collect()
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().to_string())
        .collect();

    let isep = lines.iter().position(|s| s.is_empty()).unwrap();
    let values: BTreeMap<String, u8> = lines[0..isep].iter().map(|s| parse_input(&s)).collect();
    let x0 = gather_value(&values, 'x');
    let y0 = gather_value(&values, 'y');
    let initial_gates: Vec<Gate> = lines[isep + 1..].iter().map(|s| Gate::parse(&s)).collect();

    let n = initial_gates.len();
    let ii: Vec<usize> = (0..n).collect();
    for (a, b) in (0..n).tuple_combinations() {
        let jj = without(&ii, a, b);
        for (&c, &d) in jj.iter().tuple_combinations() {
            let kk = without(&jj, c, d);
            for (&e, &f) in kk.iter().tuple_combinations() {
                let ll = without(&kk, e, f);
                for (&g, &h) in ll.iter().tuple_combinations() {
                    let mut gates = initial_gates.clone();
                    let mut swap_outputs = |i: usize, j: usize| {
                        let s = gates[i].out_id.clone();
                        let t = gates[j].out_id.clone();
                        gates[i].out_id = t;
                        gates[j].out_id = s;
                    };

                    swap_outputs(a, b);
                    swap_outputs(c, d);
                    swap_outputs(e, f);
                    swap_outputs(g, h);

                    let z = Machine::new(values.clone(), &gates).run();
                    if x0 + y0 == z {
                        let mut ans: Vec<String> = vec![];
                        ans.push(gates[a].out_id.clone());
                        ans.push(gates[b].out_id.clone());
                        ans.push(gates[c].out_id.clone());
                        ans.push(gates[d].out_id.clone());
                        ans.push(gates[e].out_id.clone());
                        ans.push(gates[f].out_id.clone());
                        ans.push(gates[g].out_id.clone());
                        ans.push(gates[h].out_id.clone());
                        asn.sort();

                        println!("{}", ans.join(","));
                    }
                }
            }
        }
    }
}
