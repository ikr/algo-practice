#include <atcoder/dsu>
#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

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

    const auto in_bounds = [&](const int ro, const int co) -> bool {
        return 0 <= ro && ro < H && 0 <= co && co < W;
    };

    atcoder::dsu cs(H * W);
    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    if (!dr && !dc) continue;

                    const auto ro_ = ro + dr;
                    const auto co_ = co + dc;
                    if (!in_bounds(ro_, co_)) continue;

                    if (grid[ro][co] == '#' && grid[ro_][co_] == '#') {
                        cs.merge(ro * W + co, ro_ * W + co_);
                    }
                }
            }
        }
    }

    unordered_set<int> leaders;
    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            if (grid[ro][co] == '#') {
                leaders.insert(cs.leader(ro * W + co));
            }
        }
    }

    cout << sz(leaders) << '\n';
    return 0;
}
