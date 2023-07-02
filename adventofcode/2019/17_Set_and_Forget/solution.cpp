#include <bits/stdc++.h>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

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

// Halts immediately if input returns a nullopt
void intcode_run(vector<ll> &xs, const function<optional<ll>(void)> input,
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

using Coord = pair<int, int>;

vector<Coord> edges(const vector<string> &grid) {
    vector<Coord> result;
    for (int ro = 1; ro < sz(grid) - 1; ++ro) {
        for (int co = 1; co < sz(grid[ro]) - 1; ++co) {
            if (grid[ro][co] == '.') continue;
            const string neighs{grid[ro - 1][co], grid[ro][co + 1],
                                grid[ro + 1][co], grid[ro][co - 1]};
            const auto deg = count_if(cbegin(neighs), cend(neighs),
                                      [](const char x) { return x != '.'; });
            if (deg == 1 || deg == 4) result.emplace_back(ro, co);
        }
    }
    return result;
}

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

    vector<string> grid{""};

    {
        const auto input = [&]() -> optional<ll> { return nullopt; };

        const auto output = [&](const ll x) -> void {
            if (x == 10) {
                grid.push_back("");
            } else {
                grid.back() += static_cast<char>(x);
            }
        };

        auto ram = rom;
        intcode_run(ram, input, output);
        while (grid.back() == "") grid.pop_back();
    }

    for (const auto &row : grid) cout << row << '\n';
    cout << '\n';

    const auto es = edges(grid);
    cout << "es[" << sz(es) << "]: " << es << '\n';

    const vector<vector<int>> adj{
        {0, 0, 12, 1},
        {0, 3, 3, 5},
        {8},
        {1, 4, 10, 1},
        {3},
        {1, 5, 5, 9},
        {8, 7, 7, 9},
        {6, 8, 9, 6},
        {6, 2, 9, 7},
        {7, 8, 5, 6},
        {3, 12, 11, 13},
        {10, 12, 13, 13},
        {10, 0, 13, 11},
        {11, 11, 12, 10},
    };

    const string full_program{
        "L,6,R,8,R,12,L,6,L,8,L,10,L,8,R,12,L,6,R,8,R,12,L,6,L,8,L,8,L,10,L,6,"
        "L,6,L,10,L,8,R,12,L,8,L,10,L,6,L,6,L,10,L,8,R,12,L,6,R,8,R,12,L,6,L,8,"
        "L,8,L,10,L,6,L,6,L,10,L,8,R,12"};

    cout << "full_program: " << full_program << "\n\n";

    const string A{"L,6,R,8,R,12,L,6,L,8"};
    const string B{"L,10,L,8,R,12"};
    const string C{"L,8,L,10,L,6,L,6"};

    const string compressed_program{"A,B,A,C,B,C,B,A,C,B"};

    {
        const string input_data =
            compressed_program + '\n' + A + '\n' + B + '\n' + C + '\n' + "y\n";
        int i{};

        const auto input = [&]() -> optional<ll> {
            return static_cast<ll>(input_data[i++]);
        };

        ll prev_x = 0;
        const auto output = [&](const ll x) -> void {
            if (x > 255) {
                cout << '\n' << x << '\n';
            } else {
                if (x == 10 && prev_x == 10) {
                    this_thread::sleep_for(chrono::milliseconds(75));
                    printf("\033[%d;%dH", 0, 0);
                } else {
                    cout << static_cast<char>(x);
                }
            }

            prev_x = x;
        };

        auto ram = rom;
        ram[0] = 2;
        intcode_run(ram, input, output);
    }

    return 0;
}
