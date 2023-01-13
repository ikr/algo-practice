#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using Coord = complex<int>;
constexpr int X(const Coord coord) { return coord.real(); }
constexpr int Y(const Coord coord) { return coord.imag(); }

struct CoordLess final {
    bool operator()(const Coord &a, const Coord &b) const {
        return (X(a) == X(b)) ? (Y(a) < Y(b)) : (X(a) < X(b));
    }
};

using Asteroids = set<Coord, CoordLess>;

constexpr int sign(const int x) { return x == 0 ? 0 : (x < 0 ? -1 : 1); }

constexpr Coord normalize(const Coord &v) {
    assert(X(v) || Y(v));
    if (!X(v)) return {0, sign(Y(v))};
    if (!Y(v)) return {sign(X(v)), 0};

    const auto g = gcd(abs(X(v)), abs(Y(v)));
    return {X(v) / g, Y(v) / g};
}

int max_observations(const Asteroids &ast) {
    int result{};
    for (const auto &a : ast) {
        int cur{};

        for (const auto &b : ast) {
            if (a == b) continue;
            const auto v = normalize(b - a);

            cur += [&]() -> bool {
                for (int k = 1;; ++k) {
                    if (k * v == b - a) break;
                    if (ast.contains(a + k * v)) return false;
                }
                return true;
            }();
        }

        result = max(result, cur);
    }
    return result;
}

int main() {
    vector<string> grid;
    for (string line; getline(cin, line);) {
        if (!empty(line)) grid.push_back(line);
    }
    assert(!grid.empty());

    Asteroids ast;
    const auto [H, W] = pair{sz(grid), sz(grid[0])};
    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            if (grid[ro][co] == '#') ast.emplace(co, ro);
        }
    }

    cout << max_observations(ast) << '\n';
    return 0;
}
