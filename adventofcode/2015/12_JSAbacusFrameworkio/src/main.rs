use serde_json::Value;

fn recur(v: &Value) -> i64 {
    match v {
        Value::Object(kvs) => {
            if kvs.values().any(|x| match x {
                Value::String(s) => s == "red",
                _ => false,
            }) {
                0
            } else {
                kvs.iter()
                    .map(|(_, el)| el)
                    .fold(0, |acc, el| acc + recur(el))
            }
        }
        Value::Array(els) => els.iter().fold(0, |acc, el| acc + recur(el)),
        Value::Number(n) => n.as_i64().unwrap(),
        _ => 0,
    }
}

fn main() {
    let src: String = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .to_owned();

    let data: Value = serde_json::from_str(&src).unwrap();
    println!("{}", recur(&data));
}
