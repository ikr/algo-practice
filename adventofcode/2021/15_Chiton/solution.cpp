#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int INF = 1e9;

int min_total_risk(const vvi &grid) {
    const int H = sz(grid);
    const int W = sz(grid[0]);

    vvi dp(H, vi(W, INF));
    dp[0][0] = 0;

    for (int co = 1; co < W; ++co) {
        dp[0][co] = dp[0][co - 1] + grid[0][co];
    }

    for (int ro = 1; ro < H; ++ro) {
        dp[ro][0] = dp[ro - 1][0] + grid[ro][0];
    }

    for (int ro = 1; ro < H; ro++) {
        for (int co = 1; co < W; ++co) {
            dp[ro][co] = min(dp[ro - 1][co], dp[ro][co - 1]) + grid[ro][co];
        }
    }

    return dp.back().back();
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
    for (const auto xs : xss) os << xs << '\n';
    return os;
}

int main() {
    vector<string> lines;

    for (string line; getline(cin, line);) {
        lines.push_back(line);
    }

    const int H = sz(lines);
    const int W = sz(lines[0]);

    vvi grid(H, vi(W, -1));
    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            grid[ro][co] = inof(lines[ro][co]) - inof('0');
        }
    }

    vvi mega_grid(5 * H, vi(5 * W, -1));
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            const auto local_val = [&](const int x) -> int {
                if (i + j == 0) return x;
                const int a = i + j;
                return ((x - 1 + a) % 9) + 1;
            };

            for (int ro = 0; ro < H; ++ro) {
                for (int co = 0; co < W; ++co) {
                    mega_grid[i * H + ro][j * W + co] = local_val(grid[ro][co]);
                }
            }
        }
    }

    cout << min_total_risk(mega_grid) << '\n';
    return 0;
}
