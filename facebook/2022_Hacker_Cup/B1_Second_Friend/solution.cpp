#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

optional<vector<string>> perfect_garden(const vector<string> &grid) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);

    if (min(H, W) > 1) return vector(H, string(W, '^'));

    if (any_of(cbegin(grid), cend(grid),
               [](const string &row) { return row.find('^') != row.npos; })) {
        return nullopt;
    }

    return grid;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int H, W;
        cin >> H >> W;

        vector<string> grid(H);
        for (auto &row : grid) {
            cin >> row;
            assert(sz(row) == W);
        }

        const auto result = perfect_garden(grid);
        cout << "Case #" << i << ": " << (result ? "Possible" : "Impossible")
             << '\n';

        if (result) {
            for (const auto &row : *result) {
                cout << row << '\n';
            }
        }
    }

    return 0;
}
