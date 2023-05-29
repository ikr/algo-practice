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

using Shape = set<Coord, CoordLess>;

enum class Dir { N = 1, S = 2, W = 3, E = 4 };
static constexpr array DirDelta{Coord{0, 1}, Coord{0, -1}, Coord{-1, 0},
                                Coord{1, 0}};

static constexpr array Compas{Dir::N, Dir::E, Dir::S, Dir::W};

enum class Stage { EXPLORE, BACKTRACK };

static constexpr ll ReplyWall = 0;
static constexpr ll ReplyMove = 1;
static constexpr ll ReplyGoal = 2;

constexpr Coord dir_delta(const Dir dir) { return DirDelta[inof(dir) - 1]; }

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

void display_frame(const Shape &space, const Shape &walls, const Coord &droid) {
    const int H = 35;
    const int W = 41;

    vector<string> grid(H, string(W, ' '));
    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            const auto x = X(droid) - W / 2 + co;
            const auto y = Y(droid) + H / 2 - ro;

            if (x == X(droid) && y == Y(droid)) {
                grid[ro][co] = '@';
            } else if (space.contains({x, y})) {
                grid[ro][co] = '.';
            } else if (walls.contains({x, y})) {
                grid[ro][co] = '#';
            }
        }
    }

    printf("\033[%d;%dH", 0, 0);
    for (const auto &row : grid) cout << row << '\n';
    cout << endl;
}

void stay_idle() { this_thread::sleep_for(chrono::milliseconds(100)); }

pair<Shape, Coord> explore_space_locate_goal(vector<ll> ram) {
    Shape space{{0, 0}};
    Shape walls;
    optional<Coord> goal;

    Coord droid{0, 0};
    stack<pair<Stage, Dir>> plan;
    for (const Dir &dir : Compas) {
        plan.emplace(Stage::EXPLORE, dir);
    }

    const auto input = [&]() -> optional<ll> {
        if (plan.empty()) return nullopt;
        const auto [_, dir] = plan.top();
        return static_cast<ll>(dir);
    };

    const auto output = [&](const ll x) -> void {
        assert(!plan.empty());
        const auto [stage, dir] = plan.top();
        plan.pop();

        switch (x) {
        case ReplyWall:
            walls.insert(droid + dir_delta(dir));
            // display_frame(space, walls, droid);
            // stay_idle();
            break;
        case ReplyMove:
            droid += dir_delta(dir);

            // display_frame(space, walls, droid);
            // stay_idle();

            if (stage == Stage::EXPLORE) {
                plan.emplace(Stage::BACKTRACK, opposite_dir(dir));
            }
            space.insert(droid);

            for (const auto &sub_dir : Compas) {
                if (!space.contains(droid + dir_delta(sub_dir)) &&
                    !walls.contains(droid + dir_delta(sub_dir))) {
                    plan.emplace(Stage::EXPLORE, sub_dir);
                }
            }
            break;
        case ReplyGoal:
            goal = droid + dir_delta(dir);
            space.insert(*goal);
            break;
        default:
            assert(false && "Invalid reply");
        }
    };

    intcode_run(ram, input, output);

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

    const auto [space, goal] = explore_space_locate_goal(ram);
    queue<Coord> plan;
    plan.emplace(0, 0);
    map<Coord, int, CoordLess> D;
    D[{0, 0}] = 0;

    while (!plan.empty()) {
        const auto u = plan.front();
        plan.pop();

        for (const auto dir : Compas) {
            const auto v = u + dir_delta(dir);
            if (space.contains(v) && !D.contains(v)) {
                D[v] = D.at(u) + 1;
                plan.push(v);
            }
        }
    }

    cout << transform_reduce(
                cbegin(D), cend(D), 0,
                [](const int x, const int y) { return max(x, y); },
                [](const auto kv) { return kv.second; })
         << endl;
    return 0;
}
