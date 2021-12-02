#include <bits/stdc++.h>
using namespace std;

int main() {
    // cin.exceptions(cin.failbit);

    int horz{};
    int depth{};
    int aim{};

    for (string line; getline(cin, line);) {
        istringstream ss{line};
        string command;
        int x;
        ss >> command >> x;

        if (command == "forward") {
            horz += x;
            depth += aim * x;
        } else if (command == "down") {
            aim += x;
        } else {
            assert(command == "up");
            aim -= x;
        }
    }

    cout << (horz * depth) << '\n';
    return 0;
}
