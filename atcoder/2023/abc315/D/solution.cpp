#include <bits/stdc++.h>
using namespace std;

static constexpr int Az = 26;
using Coord = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

array<int, Az> freqs(const string &xs) {
    array<int, Az> ans{};
    ans.fill(0);
    for (const char x : xs) ++ans[x - 'a'];
    return ans;
}

array<int, Az> freqs(const vector<string> &grid, const int co) {
    array<int, Az> ans{};
    ans.fill(0);
    for (int ro = 0; ro < sz(grid); ++ro) ++ans[grid[ro][co] - 'a'];
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int H, W;
    cin >> H >> W;

    vector<string> grid(H);
    for (auto &row : grid) {
        cin >> row;
        assert(sz(row) == W);
    }

    vector<vector<bool>> rem(H, vector(W, true));

    for (int ro = 0; ro < H; ++ro) {
        const auto fs = freqs(grid[ro]);
        for (int co = 0; co < W; ++co) {
            const int x = grid[ro][co] - 'a';
            if (fs[x] != 1) rem[ro][co] = false;
        }
    }

    for (int co = 0; co < W; ++co) {
        const auto fs = freqs(grid, co);
        for (int ro = 0; ro < H; ++ro) {
            const int x = grid[ro][co] - 'a';
            if (fs[x] != 1) rem[ro][co] = false;
        }
    }

    int ans{};
    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) ans += rem[ro][co];
    }
    cout << ans << '\n';
    return 0;
}
