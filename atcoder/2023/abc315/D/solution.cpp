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

array<int, Az> freqs(const vector<string> &grid, const vector<bool> &row_empty,
                     const int co) {
    array<int, Az> ans{};
    ans.fill(0);
    for (int ro = 0; ro < sz(grid); ++ro) {
        if (!row_empty[ro]) ++ans[grid[ro][co] - 'a'];
    }
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

    vector<vector<bool>> keep(H, vector(W, true));
    vector<bool> row_empty(H, false);

    for (int ro = 0; ro < H; ++ro) {
        const auto fs = freqs(grid[ro]);
        for (int co = 0; co < W; ++co) {
            const int x = grid[ro][co] - 'a';
            if (fs[x] == W) {
                keep[ro][co] = false;
                row_empty[ro] = true;
            }
        }
    }

    const auto empty_rows_count =
        inof(count(cbegin(row_empty), cend(row_empty), true));

    for (int co = 0; co < W; ++co) {
        const auto fs = freqs(grid, row_empty, co);

        for (int ro = 0; ro < H; ++ro) {
            const int x = grid[ro][co] - 'a';
            if (fs[x] == H - empty_rows_count) {
                keep[ro][co] = false;
            }
        }
    }

    int ans{};
    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) ans += keep[ro][co];
    }
    cout << ans << '\n';
    return 0;
}
