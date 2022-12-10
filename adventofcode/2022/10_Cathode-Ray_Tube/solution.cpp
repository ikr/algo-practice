#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> xs{};
    int carry = 1;

    for (string line; getline(cin, line);) {
        xs.push_back(carry);

        if (line.substr(0, 4) == "addx") {
            xs.push_back(carry);
            carry += stoi(line.substr(5));
        }
    }

    xs.push_back(carry);

    const auto signal_strength = [&](const int cycle) -> int {
        return cycle * xs[cycle - 1];
    };

    int result{};
    for (int i = 20; i <= 220; i += 40) {
        result += signal_strength(i);
    }
    cout << result << '\n';

    return 0;
}
