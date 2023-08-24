#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> transpose(const vector<string> &grid) {
    vector<string> result = grid;

    for (int ro = 0; ro < sz(grid); ++ro) {
        assert(sz(result) == sz(result[ro]));

        for (int co = 0; co < sz(grid); ++co) {
            result[ro][co] = grid[co][ro];
        }
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    const auto like = [&](const vector<string> &grid) -> bool {
        const auto H = sz(grid);

        for (int ro = 0; ro < H; ++ro) {
            const auto v = grid[ro].find('v');
            if (v == string::npos) continue;

            const auto i = grid[ro].find('i', v);
            if (i == string::npos) continue;

            const auto k = grid[ro].find('k', i);
            if (k == string::npos) continue;

            const auto a = grid[ro].find('a', k);
            if (a == string::npos) continue;
            return true;
        }
        return false;
    };

    {
        int t;
        cin >> t;
        while (t--) {
            int H, W;
            cin >> H >> W;

            vector<string> grid(H);
            for (auto &row : grid) {
                cin >> row;
                assert(sz(row) == W);
            }

            const auto ans = like(grid) || like(transpose(grid));
            cout << (ans ? "YES" : "NO") << '\n';
        }
    }

    return 0;
}
