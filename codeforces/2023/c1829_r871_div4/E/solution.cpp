#include <atcoder/dsu>
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll max_volume(const vector<vector<int>> &grid) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);

    atcoder::dsu uf(H * W);
    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            if (grid[ro][co] == 0) continue;

            if (ro && grid[ro - 1][co] != 0) {
                uf.merge(ro * W + co, (ro - 1) * W + co);
            }

            if (co < W - 1 && grid[ro][co + 1] != 0) {
                uf.merge(ro * W + co, ro * W + co + 1);
            }

            if (ro < H - 1 && grid[ro + 1][co] != 0) {
                uf.merge(ro * W + co, (ro + 1) * W + co);
            }

            if (co && grid[ro][co - 1] != 0) {
                uf.merge(ro * W + co, ro * W + co - 1);
            }
        }
    }

    ll ans{};
    const auto cs = uf.groups();

    for (const auto &xs : cs) {
        ll cur{};
        for (const auto x : xs) {
            const int ro = x / W;
            const int co = x % W;
            cur += grid[ro][co];
        }
        ans = max(ans, cur);
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int H, W;
        cin >> H >> W;

        vector<vector<int>> grid(H, vector(W, 0));
        for (auto &row : grid) {
            for (auto &x : row) cin >> x;
        }

        cout << max_volume(grid) << '\n';
    }

    return 0;
}
