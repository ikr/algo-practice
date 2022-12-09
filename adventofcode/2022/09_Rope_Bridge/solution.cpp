#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

struct Cmd final {
    char code;
    int arg;
};

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
    if (h == t) return t;

    const auto h_ = h + head_delta;
    if (cheb(h_, t) <= 1) return t;
    if (manh(h_, t) >= 3) return h;

    return t + head_delta;
}

int tail_areal_size(const vector<Cmd> &commands) {
    array<pii, 10> rope;
    rope.fill({0, 0});
    set<pii> tail_areal{{0, 0}};

    for (const auto &cmd : commands) {
        auto delta = parse_direction_delta(cmd.code);

        for (int k = 1; k <= cmd.arg; ++k) {
            for (int j = 1; j < sz(rope); ++j) {
                const auto rj0 = rope[j];
                rope[j] = new_tail_coord(rope[j - 1], rope[j], delta);
                rope[j - 1] = rope[j - 1] + delta;
                delta = diff(rj0, rope[j]);
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
