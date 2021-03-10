#include <bits/stdc++.h>
using namespace std;

struct Instr final {
    int op;
    int x;
    int y;

    int encode() const { return op * 100 + x * 10 + y; }
};

using Progr = array<Instr, 1000>;

constexpr Instr decode_insrt(const int code) {
    return {code / 100, (code % 100) / 10, code % 10};
}

Progr read_program() {
    Progr ans{};

    for (auto &instr : ans) {
        string line;
        if (!getline(cin, line) || line.empty()) break;
        instr = decode_insrt(stoi(line));
    }

    return ans;
}

int run_program_count_instructions(Progr p) {
    int steps{};
    int i{};
    array<int, 10> reg{};

    for (;;) {
        ++steps;

        const int op = p[i].op;
        const int x = p[i].x;
        const int y = p[i].y;

        switch (op) {
        case 1:
            assert(!x && !y);
            return steps;
        case 2:
            reg[x] = y;
            break;
        case 3:
            reg[x] += y;
            reg[x] %= 1000;
            break;
        case 4:
            reg[x] *= y;
            reg[x] %= 1000;
            break;
        case 5:
            reg[x] = reg[y];
            break;
        case 6:
            reg[x] += reg[y];
            reg[x] %= 1000;
            break;
        case 7:
            reg[x] *= reg[y];
            reg[x] %= 1000;
            break;
        case 8:
            reg[x] = p[reg[y]].encode();
            break;
        case 9:
            p[reg[y]] = decode_insrt(reg[x]);
            break;
        case 0:
            if (!!reg[y]) i = reg[x];
            break;
        default:
            assert(false && "⊙︿⊙");
            return -1;
        }

        if (op || !reg[y]) ++i;
    }

    return steps;
}

template <typename T> string join(const string &glue, const vector<T> &tokens) {
    string ans;

    for (const auto &t : tokens) {
        if (!ans.empty()) ans += glue;
        ans += to_string(t);
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

    vector<int> ans(ps.size());
    transform(ps.cbegin(), ps.cend(), begin(ans),
              run_program_count_instructions);

    cout << join("\n\n", ans) << '\n';
    return 0;
}
