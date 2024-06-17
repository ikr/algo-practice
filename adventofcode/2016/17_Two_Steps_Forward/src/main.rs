fn main() {
    let passcode: String = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .to_owned();
    eprintln!("The pass code given is {}", passcode);
}
