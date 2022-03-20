#include <cassert>
#include <iostream>
#include <string>
#include <utility>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

using pii = pair<int, int>;

enum class Dir { N = 0, E = 1, S = 2, W = 3 };

pii step(const Dir d, const pii &xy) {
    const auto [x, y] = xy;

    switch (d) {
    case Dir::N:
        return {x, y + 1};
    case Dir::E:
        return {x + 1, y};
    case Dir::S:
        return {x, y - 1};
    case Dir::W:
        return {x - 1, y};
    default:
        assert("Wrong dir");
        return xy;
    }
}

Dir turn(const Dir d) { return static_cast<Dir>((inof(d) + 1) % 4); }

pii compute(const string &s) {
    Dir d = Dir::E;
    pii xy;

    for (const auto code : s) {
        if (code == 'S') {
            xy = step(d, xy);
        } else {
            assert(code == 'R');
            d = turn(d);
        }
    }

    return xy;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    string xs;
    cin >> xs;
    assert(sz(xs) == n);

    const auto [x, y] = compute(xs);
    cout << x << ' ' << y << '\n';
    return 0;
}
