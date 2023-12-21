#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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
                break;
            }
        }
        if (src.first != -1) break;
    }
    assert(src.first != -1 && src.second != -1);

    const auto adjacent = [&](const Coord p) {
        vector<Coord> ans;
        for (const auto &d : Delta) {
            auto np = p + d;
            np.first = ((np.first % H) + H) % H;
            np.second = ((np.second % W) + W) % W;
            if (grid[np.first][np.second] == '#') continue;
            ans.push_back(np);
        }
        return ans;
    };

    const int MaxSteps = 6;

    vector<vector<int>> mul(H, vector(W, 0));
    for (int r = 0; r < H; ++r) {
        for (int c = 0; c < W; ++c) {
            if (grid[r][c] == '#') continue;
            mul[r][c] = sz(adjacent({r, c}));
        }
    }
    cerr << mul << endl;

    vector<vector<ll>> freq(H, vector(W, 0LL));
    freq[src.first][src.second] = 1;
    cerr << freq << endl;

    for (int step = 1; step <= MaxSteps; ++step) {
        vector<vector<ll>> freq_(H, vector(W, 0LL));

        for (int r = 0; r < H; ++r) {
            for (int c = 0; c < W; ++c) {
                for (const auto &p : adjacent({r, c})) {
                    freq_[p.first][p.second] += freq[r][c];
                }
            }
        }

        swap(freq, freq_);
        cerr << freq << endl;
    }

    ll result{};
    for (int r = 0; r < H; ++r) {
        for (int c = 0; c < W; ++c) {
            result += freq[r][c];
        }
    }
    cout << result << '\n';
    return 0;
}
