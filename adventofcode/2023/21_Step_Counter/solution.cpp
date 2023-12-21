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

ostream &operator<<(ostream &os, const vector<string> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
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

vector<string> multigrid(const vector<string> &grid, const int k) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);
    vector<string> result(H * k, string(W * k, ' '));
    for (int r = 0; r < H * k; ++r) {
        for (int c = 0; c < W * k; ++c) {
            result[r][c] = grid[r % H][c % W];
        }
    }
    return result;
}

int main() {
    vector<string> grid;

    for (string line; getline(cin, line);) {
        grid.push_back(line);
    }

    Coord src{-1, -1};
    for (int r = 0; r < sz(grid); ++r) {
        for (int c = 0; c < sz(grid[r]); ++c) {
            if (grid[r][c] == 'S') {
                src = {r, c};
                grid[r][c] = '.';
                break;
            }
        }
        if (src.first != -1) break;
    }
    assert(src.first != -1 && src.second != -1);

    const auto K = 1;
    src = {K / 2 * sz(grid) + src.first, K / 2 * sz(grid[0]) + src.second};
    grid = multigrid(grid, K);
    // grid[src.first][src.second] = 'S';

    const int H = sz(grid);
    const int W = sz(grid[0]);

    const int MaxSteps = 26501365;
    vector<vector<ll>> freq(H, vector(W, 0LL));
    freq[src.first][src.second] = 1;

    for (int step = 1; step <= MaxSteps; ++step) {
        vector<vector<ll>> freq_(H, vector(W, 0LL));

        for (int r = 0; r < H; ++r) {
            for (int c = 0; c < W; ++c) {
                if (grid[r][c] == '#') continue;
                vector<ll> xs;

                for (const auto &d : Delta) {
                    auto np = Coord{r, c} + d;
                    np.first = ((np.first % H) + H) % H;
                    np.second = ((np.second % W) + W) % W;
                    if (grid[np.first][np.second] == '#') continue;
                    xs.push_back(freq[np.first][np.second]);
                }

                ranges::sort(xs);
                const auto till = unique(begin(xs), end(xs));
                freq_[r][c] += accumulate(begin(xs), till, 0LL);
            }
        }

        swap(freq, freq_);
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
