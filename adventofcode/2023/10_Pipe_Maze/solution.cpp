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

using Coord = pair<int, int>;

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

static const vector<Coord> Deltas{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

static const unordered_map<char, vector<Coord>> ConnectionDeltas{
    {'|', {{-1, 0}, {1, 0}}}, {'-', {{0, -1}, {0, 1}}},
    {'L', {{-1, 0}, {0, 1}}}, {'J', {{-1, 0}, {0, -1}}},
    {'7', {{1, 0}, {0, -1}}}, {'F', {{1, 0}, {0, 1}}}};

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

Coord start_coord(const vector<string> &grid) {
    for (int ro = 0; ro < sz(grid); ++ro) {
        for (int co = 0; co < sz(grid[ro]); ++co) {
            if (grid[ro][co] == 'S') return {ro, co};
        }
    }

    assert(false && "Start missing");
    return {-1, -1};
}

int main() {
    vector<string> grid;
    for (string s; getline(cin, s);) grid.emplace_back(std::move(s));

    const auto H = sz(grid);
    const auto W = sz(grid[0]);

    const auto in_bounds = [H, W](const Coord u) {
        const auto [ro, co] = u;
        return 0 <= ro && ro < H && 0 <= co && co < W;
    };

    const auto cell = [&](const Coord u) {
        return in_bounds(u) ? grid[u.first][u.second] : ' ';
    };

    const auto is_connected = [&](const Coord u, const Coord delta) -> bool {
        const auto c = cell(u + delta);
        if (!ConnectionDeltas.contains(c)) return false;
        for (const auto &d : ConnectionDeltas.at(c)) {
            if (u + delta + d == u) return true;
        }
        return false;
    };

    const auto adjacent = [&](const Coord u) -> vector<Coord> {
        const auto c = cell(u);
        if (c == 'S') {
            vector<Coord> result;
            for (const auto &d : Deltas) {
                if (is_connected(u, d)) result.push_back(u + d);
            }
            return result;
        }

        if (!ConnectionDeltas.contains(c)) return {};
        vector<Coord> result;
        for (const auto &d : ConnectionDeltas.at(c)) {
            const auto v = u + d;
            if (in_bounds(v)) result.push_back(v);
        }
        return result;
    };

    const auto S = start_coord(grid);
    for (const auto &d : Deltas) {
        if (is_connected(S, d)) {
            cerr << S << " to " << (S + d) << endl;
        }
    }
    cerr << adjacent(S) << endl;

    return 0;
}
