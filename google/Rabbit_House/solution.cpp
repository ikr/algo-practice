#include <bits/stdc++.h>
#include <queue>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

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
    for (const auto xs : xss) os << xs << '\n';
    return os;
}

using Coord = complex<int>;
constexpr int row(const Coord coord) { return coord.real(); }
constexpr int col(const Coord coord) { return coord.imag(); }

struct q_less final {
    bool operator()(const pair<int, Coord> &a,
                    const pair<int, Coord> &b) const {
        return pair{a.first, pair{row(a.second), col(a.second)}} <
               pair{b.first, pair{row(b.second), col(b.second)}};
    }
};

using Queue =
    priority_queue<pair<int, Coord>, vector<pair<int, Coord>>, q_less>;

Queue initial_queue(const vvi &grid) {
    const int h = sz(grid);
    const int w = sz(grid[0]);
    Queue ans;

    for (int ro = 0; ro < h; ++ro) {
        for (int co = 0; co < w; ++co) {
            ans.emplace(grid[ro][co], Coord{ro, co});
        }
    }

    return ans;
}

ll solve(vvi grid) {
    const int h = sz(grid);
    const int w = sz(grid[0]);

    vector<vector<bool>> discovered(h, vector<bool>(w, false));
    auto q = initial_queue(grid);

    const auto in_bounds = [h, w](const Coord coord) {
        return row(coord) >= 0 && row(coord) < h && col(coord) >= 0 &&
               col(coord) < w;
    };

    ll ans = 0;

    while (!q.empty()) {
        const auto [_, u] = q.top();
        while (!q.empty() && u == q.top().second) q.pop();
        discovered[row(u)][col(u)] = true;

        for (const Coord d : vector<Coord>{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}) {
            const Coord v = u + d;
            if (!in_bounds(v) || discovered[row(v)][col(v)]) continue;

            const int diff = grid[row(u)][col(u)] - grid[row(v)][col(v)];
            if (diff > 1) {
                grid[row(v)][col(v)] += (diff - 1);
                ans += (diff - 1);
            }

            q.emplace(grid[row(v)][col(v)], v);
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int h, w;
        cin >> h >> w;

        vvi grid(h, vi(w, 0));
        for (auto &line : grid) {
            for (auto &cell : line) cin >> cell;
        }

        cout << "Case #" << i << ": " << solve(grid) << '\n';
    }

    return 0;
}
