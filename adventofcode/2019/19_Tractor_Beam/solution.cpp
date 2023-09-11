#include <bits/stdc++.h>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

using ll = long long;
using Coord = pair<ll, ll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
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
void run(vector<ll> &xs, const function<optional<ll>(void)> input,
         const function<void(ll)> output) {
    xs.resize(10'000, 0);
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
            const auto maybe_val = input();
            if (!maybe_val) return;

            xs[m1 == Mode::REL ? (rbase + p1) : p1] = *maybe_val;
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

vector<ll> read_rom_from_stdin() {
    string line;
    cin >> line;

    const auto tokens = split(",", line);
    vector<ll> result(sz(tokens));
    transform(cbegin(tokens), cend(tokens), begin(result),
              [](const auto &x) { return stoll(x); });

    return result;
}

int main() {
    const auto rom = read_rom_from_stdin();

    const auto confirm_beam_covers = [&](const Coord xy) -> bool {
        optional<bool> result;
        queue<ll> q;
        q.push(xy.first);
        q.push(xy.second);

        const auto input = [&]() -> optional<ll> {
            const auto a = q.front();
            q.pop();
            return a;
        };

        auto ram = rom;
        const auto output = [&](const ll a) -> void { result = (a == 1LL); };
        intcode::run(ram, input, output);

        assert(result && "No output received");
        return *result;
    };

    assert(confirm_beam_covers({0, 0}));
    for (ll x = 0; x < 50; ++x) {
        for (ll y = 0; y < 50; ++y) {
            if (confirm_beam_covers({x, y})) {
                cerr << Coord{x, y} << endl;
            }
        }
    }

    const auto left_bottom = [&]() -> Coord {
        for (ll ex = 44LL, ey = 49LL; ex < 100'000; ++ex) {
            while (confirm_beam_covers({ex, ey + 1})) ++ey;
            if (ey - 99 < 0) continue;

            const Coord right_top{ex + 99, ey - 99};
            if (confirm_beam_covers(right_top)) return {ex, ey};
        }

        return {-1, -1};
    }();

    assert(left_bottom != (Coord{-1, -1}));
    cerr << "LB: " << left_bottom << endl;

    const Coord left_top{left_bottom.first, left_bottom.second - 99};
    const auto [x0, y0] = left_top;
    cout << (x0 * 10'000LL + y0) << '\n';
    return 0;
}
