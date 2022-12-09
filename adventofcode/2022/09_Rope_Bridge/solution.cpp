#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

struct Cmd final {
    char code;
    int arg;
};

static constexpr int ROPE_SIZE = 10;
static constexpr pii DU{-1, 0};
static constexpr pii DR{0, 1};
static constexpr pii DD{1, 0};
static constexpr pii DL{0, -1};

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
        return DU;
    case 'R':
        return DR;
    case 'D':
        return DD;
    case 'L':
        return DL;
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

constexpr bool touch(const pii a, const pii b) { return cheb(a, b) <= 1; }

constexpr pii new_tail_coord(const pii moved_h, const pii t) {
    if (touch(moved_h, t)) return t;

    if (cheb(moved_h, t) == manh(moved_h, t)) {
        for (const auto &x : {t + DU, t + DR, t + DD, t + DL}) {
            if (touch(moved_h, x)) return x;
        }
        assert(false && "Impossible straight disposition");
    }

    for (const auto &x : {t + DU + DL, t + DU + DR, t + DD + DR, t + DD + DL}) {
        if (touch(moved_h, x)) return x;
    }
    assert(false && "Impossible diagonal disposition");
    return t;
}

int tail_areal_size(const vector<Cmd> &commands) {
    array<pii, ROPE_SIZE> rope;
    rope.fill({0, 0});
    set<pii> tail_areal;

    for (const auto &cmd : commands) {
        const auto head_delta = parse_direction_delta(cmd.code);

        for (int k = 1; k <= cmd.arg; ++k) {
            rope[0] = rope[0] + head_delta;

            for (int j = 1; j < sz(rope); ++j) {
                rope[j] = new_tail_coord(rope[j - 1], rope[j]);
            }

            tail_areal.insert(rope.back());
        }
    }

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
