#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

string combine_lines(const vector<string> &lines) {
    string ans;
    for (const auto &t : lines) {
        ans += t;
        ans += '\n';
    }
    return ans;
}

namespace intcode {
enum class Opcode {
    ADD = 1,
    MUL = 2,
    INP = 3,
    OUT = 4,
    JPT = 5,
    JPF = 6,
    LSS = 7,
    EQL = 8,
    RBS = 9,
    HLT = 99
};

enum class Mode { POS = 0, IMM = 1, REL = 2 };

tuple<Opcode, Mode, Mode, Mode> parse_op(ll op) {
    op = abs(op);
    const auto oc = inof(op % 100LL);

    const auto m1 = inof((op / 100LL) % 10LL);
    const auto m2 = inof((op / 1000LL) % 10LL);
    const auto m3 = inof((op / 10000LL) % 10LL);

    return {static_cast<Opcode>(oc), static_cast<Mode>(m1),
            static_cast<Mode>(m2), static_cast<Mode>(m3)};
}

// Halts immediately if input returns a nullopt
void run(vector<ll> &xs, const function<ll(void)> input,
         const function<void(ll)> output) {
    xs.resize(100'000, 0);
    int rbase{};

    const auto deref = [&](const Mode m, const ll p) -> ll {
        switch (m) {
        case Mode::POS:
            return xs[p];

        case Mode::IMM:
            return p;

        case Mode::REL:
            return xs[rbase + p];
        }

        assert(false && "/o\\");
        return 0;
    };

    for (int i = 0; 0 <= i && i < sz(xs);) {
        const auto [oc, m1, m2, m3] = parse_op(xs[i++]);

        if (oc == Opcode::ADD) {
            const auto p1 = xs[i++];
            const auto p2 = xs[i++];
            const auto p3 = xs[i++];

            assert(m3 != Mode::IMM);
            xs[m3 == Mode::REL ? (rbase + p3) : p3] =
                deref(m1, p1) + deref(m2, p2);
        } else if (oc == Opcode::MUL) {
            const auto p1 = xs[i++];
            const auto p2 = xs[i++];
            const auto p3 = xs[i++];

            assert(m3 != Mode::IMM);
            xs[m3 == Mode::REL ? (rbase + p3) : p3] =
                deref(m1, p1) * deref(m2, p2);
        } else if (oc == Opcode::INP) {
            const auto p1 = xs[i++];
            assert(m1 != Mode::IMM);
            xs[m1 == Mode::REL ? (rbase + p1) : p1] = input();
        } else if (oc == Opcode::OUT) {
            const auto p1 = xs[i++];
            output(deref(m1, p1));
        } else if (oc == Opcode::JPT) {
            const auto p1 = xs[i++];
            const auto p2 = xs[i++];
            if (deref(m1, p1)) i = inof(deref(m2, p2));
        } else if (oc == Opcode::JPF) {
            const auto p1 = xs[i++];
            const auto p2 = xs[i++];
            if (!deref(m1, p1)) i = inof(deref(m2, p2));
        } else if (oc == Opcode::LSS) {
            const auto p1 = xs[i++];
            const auto p2 = xs[i++];
            const auto p3 = xs[i++];

            assert(m3 != Mode::IMM);
            xs[m3 == Mode::REL ? (rbase + p3) : p3] =
                deref(m1, p1) < deref(m2, p2);
        } else if (oc == Opcode::EQL) {
            const auto p1 = xs[i++];
            const auto p2 = xs[i++];
            const auto p3 = xs[i++];

            assert(m3 != Mode::IMM);
            xs[m3 == Mode::REL ? (rbase + p3) : p3] =
                deref(m1, p1) == deref(m2, p2);
        } else if (oc == Opcode::RBS) {
            const auto p1 = xs[i++];
            rbase += inof(deref(m1, p1));
        } else if (oc == Opcode::HLT) {
            break;
        } else {
            assert(false && "Invalid opcode");
        }
    }
}
} // namespace intcode

static constexpr int NicsNum = 50;

struct Transmit final {
    ll address;
    pair<ll, ll> xy;
};

struct Terminate final {
    ll result;
};

using Output = variant<Transmit, Terminate>;

template <class... Ts> struct overloaded : Ts... {
    using Ts::operator()...;
};

int main() {
    const auto rom = [&]() -> vector<ll> {
        string line;
        cin >> line;

        const auto tokens = split(",", line);
        vector<ll> result(sz(tokens));
        transform(cbegin(tokens), cend(tokens), begin(result),
                  [](const auto &x) { return stoll(x); });
        return result;
    }();

    vector<vector<ll>> ram(NicsNum, rom);
    vector<queue<ll>> istream(NicsNum);
    for (int i = 0; i < NicsNum; ++i) istream[i].push(i);

    const auto tick = [&](const int i) -> Output {
        const auto input = [&]() -> ll {
            if (istream[i].empty()) return -1;
            const auto result = istream[i].front();
            istream[i].pop();
            return result;
        };

        optional<ll> a, x, y;
        const auto output = [&](const ll v) {
            if (!a) {
                a = v;
            } else if (!x) {
                x = v;
            } else if (!y) {
                y = v;
            } else {
                assert(false && "Too many values put out");
            }
        };

        intcode::run(ram[i], input, output);
        assert(a && x && y);

        if (*a == 255) return Terminate{*y};
        return Transmit{*a, {*x, *y}};
    };

    for (int i = 0;; i = (i + 1) % NicsNum) {
        const auto output = tick(i);
        const auto go_on =
            visit(overloaded{
                      [&](const Transmit &t) -> bool {
                          assert(0 <= t.address && t.address < NicsNum);
                          istream[t.address].push(t.xy.first);
                          istream[t.address].push(t.xy.second);
                          return true;
                      },
                      [&](const Terminate &t) -> bool {
                          cout << t.result << '\n';
                          return false;
                      },
                  },
                  output);
        if (!go_on) break;
    }

    return 0;
}
