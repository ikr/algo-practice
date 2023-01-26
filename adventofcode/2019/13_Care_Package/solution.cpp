#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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

using Coord = pair<int, int>;
enum class Phase { X, Y, TILE };
enum class Tile { WALL = 1, BLOCK, PADDLE, BALL };

constexpr Phase next_phase(const Phase a) {
    return static_cast<Phase>((inof(a) + 1) % 3);
}

int main() {
    string line;
    cin >> line;

    const auto tokens = split(",", line);
    vector<ll> xs(sz(tokens));
    transform(cbegin(tokens), cend(tokens), begin(xs),
              [](const auto &x) { return stoll(x); });

    map<Coord, Tile> grid;
    Phase phase = Phase::X;
    Coord xy{INT_MIN, INT_MIN};

    const auto input = [&]() -> ll { return 0; };

    const auto output = [&](const ll a) -> void {
        switch (phase) {
        case Phase::X:
            xy.first = a;
            break;
        case Phase::Y:
            xy.second = a;
            break;
        case Phase::TILE:
            if (!a) {
                grid.erase(xy);
            } else {
                grid[xy] = static_cast<Tile>(a);
            }
            break;
        }

        phase = next_phase(phase);
    };

    intcode_run(move(xs), input, output);

    int ans{};
    for (const auto &[_, tile] : grid) ans += tile == Tile::BLOCK;

    cout << ans << '\n';
    return 0;
}
