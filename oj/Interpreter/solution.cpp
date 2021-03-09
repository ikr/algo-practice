#include <bits/stdc++.h>
using namespace std;

struct Instr final {
    int op;
    int x;
    int y;
};

string op_description(const int op) {
    switch (op) {
    case 1:
        return "halt";
    case 2:
        return "reg x := y";
    case 3:
        return "reg x += y";
    case 4:
        return "reg x *= y";
    case 5:
        return "reg x := reg y";
    case 6:
        return "reg x += reg y";
    case 7:
        return "reg x *= reg y";
    case 8:
        return "reg x := ram[reg y]";
    case 9:
        return "ram[reg y] := reg x";
    case 0:
        return "goto (reg x) ⇔ ‼reg y";
    default:
        return "¯\\_(ツ)_/¯";
    }
}

ostream &operator<<(ostream &os, const Instr &instr) {
    os << '(' << op_description(instr.op) << " ∘ " << instr.x << " ∘ "
       << instr.y << ')';
    return os;
}

using Progr = array<Instr, 1000>;

constexpr Instr decode_insrt(const int code) {
    return {code / 100, (code % 100) / 10, code % 10};
}

Progr read_program() {
    Progr ans;
    for (auto &instr : ans) instr = {0, 0, 0};

    for (auto &instr : ans) {
        string line;
        if (!getline(cin, line) || line.empty()) break;
        instr = decode_insrt(stoi(line));
    }

    return ans;
}

int main() {
    int t;
    cin >> t;

    string line;
    getline(cin, line);
    getline(cin, line);

    vector<Progr> ps;
    for (int i = 0; i < t; ++i) ps.push_back(read_program());

    return 0;
}
