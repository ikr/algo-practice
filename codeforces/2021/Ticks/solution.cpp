#include <bits/stdc++.h>
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

bool in_bounds(const vector<string> &grid, const int ro, const int co) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);
    return 0 <= ro && ro < H && 0 <= co && co < W;
}

bool is_bottom(const vector<string> &grid, const int K, const pii roco) {
    const auto [ro, co] = roco;

    for (int d = 1; d <= K; ++d) {
        if (!in_bounds(grid, ro - d, co - d)) return false;
        if (grid[ro - d][co - d] != '*') return false;
        if (!in_bounds(grid, ro - d, co + d)) return false;
        if (grid[ro - d][co + d] != '*') return false;
    }

    return true;
}

bool is_possible(const vector<string> &grid, const int K) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);

    vector<vector<bool>> ok(H, vector(W, false));
    set<pii> q;

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            if (grid[ro][co] == '.') {
                ok[ro][co] = true;
            } else {
                q.emplace(ro, co);
            }
        }
    }

    while (!q.empty()) {
        const auto [ro, co] = *crbegin(q);
        q.erase(prev(cend(q)));

        if (is_bottom(grid, K, {ro, co})) {
            ok[ro][co] = true;

            for (int d = 1; in_bounds(grid, ro - d, co - d) &&
                            (grid[ro - d][co - d] == '*') &&
                            in_bounds(grid, ro - d, co + d) &&
                            (grid[ro - d][co + d] == '*');
                 ++d) {
                ok[ro - d][co - d] = true;
                ok[ro - d][co + d] = true;
            }
        }
    }

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            if (!ok[ro][co]) return false;
        }
    }
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int H, W, K;
        cin >> H >> W >> K;

        vector<string> grid(H, string(W, ' '));
        for (auto &row : grid) {
            cin >> row;
        }

        cout << (is_possible(grid, K) ? "YES" : "NO") << '\n';
    }

    return 0;
}
