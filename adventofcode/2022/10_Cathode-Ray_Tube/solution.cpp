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

    vector<string> grid(6, string(40, '.'));
    for (int ro = 0; ro < 6; ++ro) {
        for (int co = 0; co < 40; ++co) {
            const int cycle = ro * 40 + co;
            if (abs(xs[cycle] - co) <= 1) {
                grid[ro][co] = '#';
            }
        }
    }

    for (const auto &row : grid) cout << row << '\n';
    return 0;
}
