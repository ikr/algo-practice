#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using Coord = pair<ll, ll>;

enum class Dir { Up, Right, Down, Left };
static constexpr array Delta{Coord{-1, 0}, Coord{0, 1}, Coord{1, 0},
                             Coord{0, -1}};

constexpr Coord delta_of(const Dir dir) {
    const int i = static_cast<int>(dir);
    assert(0 <= i && i < ssize(Delta));
    return Delta[i];
}

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

template <typename T>
constexpr pair<T, T> operator-(const pair<T, T> a, const pair<T, T> b) {
    return {a.first - b.first, a.second - b.second};
}

template <typename T>
constexpr pair<T, T> scaled_by(const pair<T, T> ab, const T k) {
    return {k * ab.first, k * ab.second};
}

pair<Dir, ll> decode_step(const string &src) {
    const auto distance = stoll(src.substr(0, 5), nullptr, 16);
    const auto dir = [&]() -> Dir {
        switch (src.back()) {
        case '3':
            return Dir::Up;
        case '0':
            return Dir::Right;
        case '1':
            return Dir::Down;
        case '2':
            return Dir::Left;
        default:
            assert(false);
        }
    }();
    return {dir, distance};
}

int main() {
    vector<Coord> path{{0, 0}};

    for (string line; getline(cin, line);) {
        auto token = line.substr(sz(line) - 7);
        token.pop_back();
        const auto [dir, distance] = decode_step(token);
        path.push_back(path.back() + scaled_by(delta_of(dir), distance));
    }
    assert(path[0] == path.back());

    ll border{};
    for (int i = 1; i < sz(path); ++i) {
        const auto [dx, dy] = path[i] - path[i - 1];
        border += abs(dx) + abs(dy);
    }

    ranges::reverse(path);

    ll total{};
    for (int i = 0; i < sz(path) - 1; ++i) {
        total += 1LL * path[i].first * path[i + 1].second -
                 1LL * path[i].second * path[i + 1].first;
    }
    cout << (total + border) / 2LL + 1 << '\n';
    return 0;
}
