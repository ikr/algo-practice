#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using pii = pair<int, int>;

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

    vector<pii> ps;

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            if (grid[ro][co] == 'o') {
                ps.emplace_back(ro, co);
            }
        }
    }

    assert(sz(ps) == 2);

    const auto [ro1, co1] = ps[0];
    const auto [ro2, co2] = ps[1];
    const auto ans = abs(ro1 - ro2) + abs(co1 - co2);
    cout << ans << '\n';
    return 0;
}
