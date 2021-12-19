#include <bits/stdc++.h>
using namespace std;

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

using vi = vector<int>;
using vvi = vector<vi>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int max_visited(const vector<string> &grid) {
    const int H = sz(grid);
    const int W = sz(grid[0]);

    vvi dp(H, vi(W, 0));
    dp[0][0] = 1;

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            if (grid[ro][co] == '#' || dp[ro][co] == 0) continue;

            if (co < W - 1 && grid[ro][co + 1] != '#') {
                dp[ro][co + 1] = max(dp[ro][co + 1], dp[ro][co] + 1);
            }

            if (ro < H - 1 && grid[ro + 1][co] != '#') {
                dp[ro + 1][co] = max(dp[ro + 1][co], dp[ro][co] + 1);
            }
        }
    }

    int ans{};
    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            ans = max(ans, dp[ro][co]);
        }
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int H, W;
    cin >> H >> W;

    vector<string> grid(H, string(W, ' '));
    for (auto &row : grid) cin >> row;

    cout << max_visited(grid) << '\n';
    return 0;
}
