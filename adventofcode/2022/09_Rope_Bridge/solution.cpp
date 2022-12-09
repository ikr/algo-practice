#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

struct Cmd final {
    char code;
    int arg;
};

static constexpr int ROPE_SIZE = 10;

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr pii parse_direction_delta(const char x) {
    switch (x) {
    case 'U':
        return {-1, 0};
    case 'R':
        return {0, 1};
    case 'D':
        return {1, 0};
    case 'L':
        return {0, -1};
    default:
        assert(false && "Unknown direction code");
        return {0, 0};
    }
}

constexpr int manh(const pii a, const pii b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

constexpr int cheb(const pii a, const pii b) {
    return max(abs(a.first - b.first), abs(a.second - b.second));
}

constexpr pii diff(const pii a, const pii b) {
    return {b.first - a.first, b.second - a.second};
}

constexpr pii new_tail_coord(const pii h, const pii t, const pii head_delta) {
    const auto h_ = h + head_delta;

    if (cheb(h_, t) <= 1) return t;
    if (manh({0, 0}, head_delta) == 2) return t + head_delta;
    if (manh(h_, t) == 3) return h;

    return t + head_delta;
}

vector<string> visualize(const array<pii, ROPE_SIZE> &rope) {
    const int H{21};
    const int W{26};
    const int ORO = 16;
    const int OCO = 12;
    vector<string> grid(H, string(W, '.'));

    grid[ORO - 1][OCO - 1] = 's';

    for (int i = sz(rope) - 1; i >= 1; --i) {
        grid[rope[i].first + ORO - 1][rope[i].second + OCO - 1] =
            static_cast<char>(inof('0') + i);
    }
    grid[rope[0].first + ORO - 1][rope[0].second + OCO - 1] = 'H';

    return grid;
}

void dbg(const vector<string> &grid) {
    for (const auto &row : grid) cerr << row << '\n';
    cerr << endl;
}

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

template <typename T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

int tail_areal_size(const vector<Cmd> &commands) {
    array<pii, ROPE_SIZE> rope;
    rope.fill({0, 0});
    set<pii> tail_areal;

    for (const auto &cmd : commands) {
        for (int k = 1; k <= cmd.arg; ++k) {
            auto delta = parse_direction_delta(cmd.code);
            auto rope_ = rope;

            for (int j = 1; j < sz(rope); ++j) {
                rope_[j] = new_tail_coord(rope[j - 1], rope[j], delta);
                delta = diff(rope[j], rope_[j]);
            }

            rope_[0] = rope[0] + parse_direction_delta(cmd.code);
            swap(rope, rope_);
            tail_areal.insert(rope.back());
        }

        dbg(visualize(rope));
    }

    cerr << rope << endl;
    return sz(tail_areal);
}

int main() {
    vector<Cmd> commands;
    for (string line; getline(cin, line);) {
        commands.push_back(Cmd{line[0], stoi(line.substr(2))});
    }

    cout << tail_areal_size(commands) << '\n';
    return 0;
}
