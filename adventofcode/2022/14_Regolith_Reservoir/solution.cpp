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

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
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

using Coord = pair<int, int>;
using Waypoints = vector<Coord>;

constexpr int X(const Coord c) { return c.first; }
constexpr int Y(const Coord c) { return c.second; }

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

constexpr int step_from_to(const int a, const int b) {
    if (a == b) return 0;
    return a < b ? 1 : -1;
}

constexpr Coord step_from_to(const Coord a, const Coord b) {
    return {step_from_to(X(a), X(b)), step_from_to(Y(a), Y(b))};
}

Coord parse_coord(const string &src) {
    const auto parts = split(",", src);
    assert(sz(parts) == 2);
    return {stoi(parts[0]), stoi(parts[1])};
}

Coord dimensions(const vector<Waypoints> &wpss) {
    int x_max{};
    int y_max{};

    for (const auto &wps : wpss) {
        for (const auto &[x, y] : wps) {
            x_max = max(x_max, x);
            y_max = max(y_max, y);
        }
    }

    return {x_max, y_max};
}

pair<vector<string>, Coord> structural_grid(const vector<Waypoints> &wpss,
                                            const Coord src_) {
    const auto [x_max, y_max] = dimensions(wpss);
    vector<string> result(y_max + 2, string(x_max + 3, '.'));

    for (const auto &wps : wpss) {
        for (int i = 1; i < sz(wps); ++i) {
            const auto step = step_from_to(wps[i - 1], wps[i]);

            for (auto cur = wps[i - 1];; cur = cur + step) {
                result[Y(cur)][X(cur) + 1] = '#';
                if (cur == wps[i]) break;
            }
        }
    }

    const Coord src{X(src_) + 1, Y(src_)};
    result[Y(src)][X(src)] = '+';
    return {result, src};
}

int simulation_steps_until_stable(const vector<Waypoints> &wpss,
                                  const Coord src_) {
    auto [grid, src] = structural_grid(wpss, src_);

    for (const auto &row : grid) {
        cout << row << '\n';
    }

    return -1;
}

int main() {
    vector<Waypoints> wpss;

    for (string line; getline(cin, line);) {
        const auto point_sources = split(" -> ", line);
        Waypoints wps(sz(point_sources));
        transform(cbegin(point_sources), cend(point_sources), begin(wps),
                  parse_coord);
        wpss.push_back(wps);
    }

    cerr << wpss << endl;

    cout << simulation_steps_until_stable(wpss, {5, 0}) << '\n';
    return 0;
}
