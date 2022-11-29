#include <bits/stdc++.h>
using namespace std;

enum class Opcode {
    ADD = 1,
    MUL = 2,
    INP = 3,
    OUT = 4,
    JPT = 5,
    JPF = 6,
    LSS = 7,
    EQL = 8,
    HLT = 99
};

enum class Mode { POS = 0, IMM = 1 };

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

tuple<Opcode, Mode, Mode> parse_op(const int op) {
    return {static_cast<Opcode>(op % 100), static_cast<Mode>((op / 100) % 10),
            static_cast<Mode>((op / 1000) % 10)};
}

int input() { return 5; }
void output(const int x) { cout << x << '\n'; }

void intcode_run(vector<int> xs) {
    const auto deref = [&xs](const Mode m, const int p) -> int {
        return m == Mode::POS ? xs[p] : p;
    };

    for (int i = 0; i < sz(xs);) {
        const auto [oc, m1, m2] = parse_op(xs[i++]);

        if (oc == Opcode::ADD) {
            const auto p1 = xs[i++];
            const auto p2 = xs[i++];
            const auto p3 = xs[i++];
            xs[p3] = deref(m1, p1) + deref(m2, p2);
        } else if (oc == Opcode::MUL) {
            const auto p1 = xs[i++];
            const auto p2 = xs[i++];
            const auto p3 = xs[i++];
            xs[p3] = deref(m1, p1) * deref(m2, p2);
        } else if (oc == Opcode::INP) {
            xs[xs[i++]] = input();
        } else if (oc == Opcode::OUT) {
            const auto p1 = xs[i++];
            output(deref(m1, p1));
            continue;
        } else if (oc == Opcode::JPT) {
            const auto p1 = xs[i++];
            const auto p2 = xs[i++];
            if (deref(m1, p1)) i = deref(m2, p2);
            continue;
        } else if (oc == Opcode::JPF) {
            const auto p1 = xs[i++];
            const auto p2 = xs[i++];
            if (!deref(m1, p1)) i = deref(m2, p2);
        } else if (oc == Opcode::LSS) {
            const auto p1 = xs[i++];
            const auto p2 = xs[i++];
            const auto p3 = xs[i++];
            xs[p3] = deref(m1, p1) < deref(m2, p2);
        } else if (oc == Opcode::EQL) {
            const auto p1 = xs[i++];
            const auto p2 = xs[i++];
            const auto p3 = xs[i++];
            xs[p3] = deref(m1, p1) == deref(m2, p2);
        } else if (oc == Opcode::HLT) {
            break;
        } else {
            assert(false && "Invalid opcode");
        }
    }
}

int main() {
    string line;
    cin >> line;

    const auto tokens = split(",", line);
    vector<int> xs(sz(tokens));
    transform(cbegin(tokens), cend(tokens), begin(xs),
              [](const auto &x) { return stoi(x); });
    intcode_run(move(xs));
    return 0;
}
