#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> ostream &operator<<(ostream &os, const optional<T> o) {
    if (!o) {
        os << "nullopt";
    } else {
        os << *o;
    }
    return os;
}

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

template <typename T> ostream &operator<<(ostream &os, const set<T> &xs) {
    os << '{';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << '}';
    return os;
}

template <typename T>
ostream &operator<<(ostream &os, const unordered_set<T> &xs) {
    os << '{';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << '}';
    return os;
}

template <typename K, typename V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
    os << '{';
    for (auto i = m.cbegin(); i != m.cend(); ++i) {
        if (i != m.cbegin()) os << ' ';
        os << '(' << i->first << ' ' << i->second << ')';
    }
    os << '}';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using Coord = pair<int, int>;

static constexpr array Delta{Coord{-1, 0}, Coord{0, 1}, Coord{1, 0},
                             Coord{0, -1}};

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

int main() {
    vector<string> grid;

    for (string line; getline(cin, line);) {
        grid.push_back(line);
    }

    const int H = sz(grid);
    const int W = sz(grid[0]);
    Coord src{-1, -1};

    for (int r = 0; r < H; ++r) {
        for (int c = 0; c < W; ++c) {
            if (grid[r][c] == 'S') {
                src = {r, c};
            }
        }
    }
    assert(src.first != -1 && src.second != -1);

    const auto inf_grid_at = [&](const Coord p) -> char {
        const auto r = ((p.first % H) + H) % H;
        const auto c = ((p.second % W) + W) % W;
        return grid[r][c];
    };

    const auto adjacent = [&](const Coord p) {
        vector<Coord> ans;
        for (const auto &d : Delta) {
            const auto np = p + d;
            if (inf_grid_at(np) == '#') continue;
            ans.push_back(np);
        }
        return ans;
    };

    const int MaxSteps = 500;

    map<int, set<Coord>> by_step;
    by_step[0] = {src};

    vector<int> xs;

    for (int step = 1; step <= MaxSteps; ++step) {
        for (const auto &p : by_step[step - 1]) {
            for (const auto &np : adjacent(p)) {
                by_step[step].insert(np);
            }
        }
        xs.push_back(sz(by_step[step]));
    }

    vector<int> ys(sz(xs));
    adjacent_difference(cbegin(xs), cend(xs), begin(ys));

    vector<int> zs(sz(xs));
    adjacent_difference(cbegin(ys), cend(ys), begin(zs));

    cout << xs << endl;
    cout << ys << endl;
    cout << zs << endl;

    cout << sz(by_step[MaxSteps]) << endl;
    return 0;
}
