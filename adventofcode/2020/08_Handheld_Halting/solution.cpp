#include <bits/stdc++.h>
using namespace std;

enum class Instr { NOP, JMP, ACC };

pair<Instr, int> parse_instr(const string &code, const string &arg) {
    const int x = stoi(arg);
    if (code == "nop") return {Instr::NOP, x};
    if (code == "acc") return {Instr::ACC, x};
    return {Instr::JMP, x};
}

int execute(const vector<pair<Instr, int>> &program) {
    const int n = program.size();
    vector<bool> done(n, false);
    int ans = 0;
    int pointer = 0;

    while (!done[pointer]) {
        done[pointer] = true;

        const auto [op, arg] = program.at(pointer);
        if (op == Instr::NOP) {
            ++pointer;
        } else if (op == Instr::ACC) {
            ans += arg;
            ++pointer;
        } else {
            pointer += arg;
        }

        pointer = ((pointer % n) + n) % n;
    }

    return ans;
}

int main() {
    vector<pair<Instr, int>> program;

    for (string line; getline(cin, line);) {
        const auto s1 = line.substr(0, 3);
        const auto s2 = line.substr(3);
        program.push_back(parse_instr(s1, s2));
    }

    cout << execute(program) << '\n';
    return 0;
}
