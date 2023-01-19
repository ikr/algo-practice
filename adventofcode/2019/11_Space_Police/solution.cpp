#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

enum class Phase { PAINTING = 0, MOVING = 1 };
enum class Direction { NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3 };

static const vector<pii> DELTAS = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

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

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

tuple<Opcode, Mode, Mode, Mode> parse_op(ll op) {
    op = abs(op);
    const auto oc = inof(op % 100LL);

    const auto m1 = inof((op / 100LL) % 10LL);
    const auto m2 = inof((op / 1000LL) % 10LL);
    const auto m3 = inof((op / 10000LL) % 10LL);

    return {static_cast<Opcode>(oc), static_cast<Mode>(m1),
            static_cast<Mode>(m2), static_cast<Mode>(m3)};
}

void intcode_run(vector<ll> xs, const function<ll(void)> input,
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

template <int M, typename T> constexpr T cycle_forward(const T t) {
    return static_cast<T>((inof(t) + 1) % M);
}

template <int M, typename T> constexpr T cycle_back(const T t) {
    return static_cast<T>((((inof(t) - 1) % M) + M) % M);
}

int main() {
    string line;
    cin >> line;

    const auto tokens = split(",", line);
    vector<ll> xs(sz(tokens));
    transform(cbegin(tokens), cend(tokens), begin(xs),
              [](const auto &x) { return stoll(x); });

    set<pii> black;
    pii roco{0, 0};
    Direction dir{Direction::NORTH};
    Phase phase{Phase::PAINTING};

    const auto input = [&]() -> ll { return black.contains(roco) ? 0 : 1; };

    const auto output = [&](const ll x) -> void {
        if (phase == Phase::PAINTING) {
            if (x == 0) {
                black.insert(roco);
            } else {
                black.erase(roco);
            }
        } else {
            if (x == 0) {
                dir = cycle_back<4>(dir);
            } else {
                dir = cycle_forward<4>(dir);
            }

            roco = roco + DELTAS[inof(dir)];
        }
        phase = cycle_forward<2>(phase);
    };

    intcode_run(move(xs), input, output);
    cout << sz(black) << '\n';
    return 0;
}
