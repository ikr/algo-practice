#include <bits/stdc++.h>
using namespace std;

template <typename T, typename L>
ostream &operator<<(ostream &os, const set<T, L> &xs) {
    os << '{';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << '}';
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

using Coord = complex<int>;
constexpr int X(const Coord coord) { return coord.real(); }
constexpr int Y(const Coord coord) { return coord.imag(); }

struct CoordLess final {
    bool operator()(const Coord &a, const Coord &b) const {
        return (X(a) == X(b)) ? (Y(a) < Y(b)) : (X(a) < X(b));
    }
};

ostream &operator<<(ostream &os, const Coord &xy) {
    os << '(' << X(xy) << ' ' << Y(xy) << ')';
    return os;
}

bool are_adjacent(const Coord &a, const Coord &b) {
    return norm<int>(a - b) == 1;
}

using Space = set<Coord, CoordLess>;

enum class Dir { N = 1, S = 2, W = 3, E = 4 };
static const array DirDelta{Coord{0, 1}, Coord{0, -1}, Coord{-1, 0},
                            Coord{1, 0}};

static constexpr ll ReplyWall = 0;
static constexpr ll ReplyMove = 1;
static constexpr ll ReplyGoal = 2;

Dir opposite_dir(const Dir d) {
    switch (d) {
    case Dir::N:
        return Dir::S;
    case Dir::S:
        return Dir::N;
    case Dir::W:
        return Dir::E;
    case Dir::E:
        return Dir::W;
    }

    assert(false && "Impossible direction in `opposite`");
    return Dir::N;
}

Dir next_dir(const Dir d) {
    static const array seq{Dir::N, Dir::E, Dir::S, Dir::W};
    const auto i = inof(find(cbegin(seq), cend(seq), d) - cbegin(seq));
    return seq[(i + 1) % sz(seq)];
}

pair<Space, Coord> explore_space_locate_goal(vector<ll> ram) {
    Space space{{0, 0}};
    optional<Coord> goal;

    Coord droid{0, 0};
    stack<Dir> st;
    st.push(Dir::N);

    const auto input = [&]() -> optional<ll> {
        if (st.empty() || goal) return nullopt;
        const auto dir = st.top();
        const auto delta = DirDelta[inof(dir) - 1];
        return static_cast<ll>(dir);
    };

    const auto output = [&](const ll x) -> void {
        assert(!st.empty());
        const auto dir = st.top();
        st.pop();
        const auto delta = DirDelta[inof(dir) - 1];

        switch (x) {
        case ReplyWall:
            cerr << "Wall!" << endl;
            break;
        case ReplyMove:
            droid += delta;
            space.insert(droid);
            break;
        case ReplyGoal:
            *goal = droid + delta;
            break;
        default:
            assert(false && "Invalid reply");
        }
    };

    intcode_run(ram, input, output);
    cerr << space << endl;
    assert(goal);
    return {space, *goal};
}

int main() {
    string line;
    cin >> line;

    const auto tokens = split(",", line);
    vector<ll> ram(sz(tokens));
    transform(cbegin(tokens), cend(tokens), begin(ram),
              [](const auto &x) { return stoll(x); });

    explore_space_locate_goal(ram);
    return 0;
}
