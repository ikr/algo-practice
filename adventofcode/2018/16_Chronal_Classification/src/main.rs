fn read_input_parts() -> (String, String) {
    match std::io::read_to_string(std::io::stdin()) {
        Ok(s) => {
            let parts = s.split("\n\n\n").collect::<Vec<&str>>();
            (parts[0].to_string(), parts[1].to_string())
        }
        Err(e) => panic!("Error reading from stdin: {}", e),
    }
}

fn main() {
    let (samples, _) = read_input_parts();
    eprintln!("{}", samples);
}
