#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr long double ldof(const T x) {
    return static_cast<long double>(x);
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using ld = long double;
using Coord = complex<int>;
constexpr int X(const Coord coord) { return coord.real(); }
constexpr int Y(const Coord coord) { return coord.imag(); }

struct CoordLess final {
    bool operator()(const Coord &a, const Coord &b) const {
        return (X(a) == X(b)) ? (Y(a) < Y(b)) : (X(a) < X(b));
    }
};

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

ostream &operator<<(ostream &os, const Coord &c) {
    os << '(' << X(c) << ' ' << Y(c) << ')';
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

using Asteroids = set<Coord, CoordLess>;

constexpr int sign(const int x) { return x == 0 ? 0 : (x < 0 ? -1 : 1); }

constexpr Coord normalize(const Coord &v) {
    assert(X(v) || Y(v));
    if (!X(v)) return {0, sign(Y(v))};
    if (!Y(v)) return {sign(X(v)), 0};

    const auto g = gcd(abs(X(v)), abs(Y(v)));
    return {X(v) / g, Y(v) / g};
}

pair<vector<Coord>, Coord> most_observations_from(const Asteroids &ast) {
    vector<Coord> result;
    Coord vintage_point{0, 0};

    for (const auto &a : ast) {
        vector<Coord> cur;

        for (const auto &b : ast) {
            if (a == b) continue;
            const auto v = normalize(b - a);

            const auto is_visible = [&]() -> bool {
                for (int k = 1;; ++k) {
                    if (k * v == b - a) break;
                    if (ast.contains(a + k * v)) return false;
                }
                return true;
            }();

            if (is_visible) cur.push_back(b);
        }

        if (sz(cur) > sz(result)) {
            swap(cur, result);
            vintage_point = a;
        }
    }

    return {result, vintage_point};
}

ld real_length(const Coord &u) {
    return abs(complex<ld>{ldof(X(u)), ldof(Y(u))});
}

ld angle_between(const Coord &u, const Coord &v) {
    const auto dot_product = ldof(X(u) * X(v) + Y(u) * Y(v));
    const auto cos_theta = dot_product / (real_length(u) * real_length(v));
    return acosl(cos_theta);
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

    auto scene = most_observations_from(ast);

    const auto clocklike_rotation_angle = [&](const Coord &b) -> ld {
        const auto a = scene.second;
        const auto v = b - a;

        if (X(v) >= 0) {
            return angle_between({0, -1}, v);
        } else {
            return numbers::pi_v<ld> + angle_between({0, 1}, v);
        }
    };

    auto &surrounding = scene.first;
    sort(begin(surrounding), end(surrounding),
         [&](const Coord &a, const Coord &b) -> bool {
             return clocklike_rotation_angle(a) < clocklike_rotation_angle(b);
         });

    cerr << scene << endl;

    const auto result = surrounding[199];
    cout << result << ' ' << X(result) * 100 + Y(result) << '\n';
    return 0;
}
