#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr bool is_interesting(const char x) {
    return x == 'v' || x == 'i' || x == 'k' || x == 'a';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

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

        vector<set<char>> seen(W);

        for (int co = 0; co < W; ++co) {
            for (int ro = 0; ro < H; ++ro) {
                if (is_interesting(grid[ro][co])) {
                    seen[co].insert(grid[ro][co]);
                }
            }
        }

        const auto ans = [&]() -> bool {
            const string pat{"vika"};
            int i = 0;

            for (const auto &xs : seen) {
                if (i == sz(pat)) break;

                if (xs.contains(pat[i])) {
                    ++i;
                }
            }

            return i == sz(pat);
        }();

        cout << (ans ? "YES" : "NO") << '\n';
    }

    return 0;
}
