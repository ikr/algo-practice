#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int H, W, T;
    cin >> H >> W >> T;

    vector<string> grid(H);
    for (auto &row : grid) {
        cin >> row;
        assert(sz(row) == W);
    }

    pii start{}, goal{};
    vector<pii> candies;

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            switch (grid[ro][co]) {
            case 'S':
                start = pii{ro, co};
                break;
            case 'G':
                goal = pii{ro, co};
                break;
            case 'o':
                candies.emplace_back(ro, co);
            }
        }
    }

    const auto n = sz(candies) + 2;
    vector<vector<pii>> g(n);

    return 0;
}
