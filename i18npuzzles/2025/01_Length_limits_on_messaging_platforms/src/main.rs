use std::io::{self, BufRead};

const MAX_SMS_BYTES: usize = 160;
const MAX_TWEET_CHARS: usize = 140;

fn message_cost(sms: bool, tweet: bool) -> u32 {
    match (sms, tweet) {
        (false, false) => 0,
        (false, true) => 7,
        (true, false) => 11,
        (true, true) => 13,
    }
}

fn main() {
    let xs: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap())
        .collect();

    let char_lengths: Vec<usize> = xs.iter().map(|x| x.chars().count()).collect();
    let byte_lengths: Vec<usize> = xs.into_iter().map(|x| x.len()).collect();

    let costs: Vec<u32> = char_lengths
        .into_iter()
        .zip(byte_lengths.iter())
        .map(|(c, b)| (*b <= MAX_SMS_BYTES, c <= MAX_TWEET_CHARS))
        .map(|(sms, tweet)| message_cost(sms, tweet))
        .collect();

    let result: u32 = costs.into_iter().sum();
    println!("{}", result);
}
