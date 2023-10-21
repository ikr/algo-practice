#include <atcoder/dsu>
#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static const vector<pii> Deltas{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

constexpr pii roco_of(const int W, const int code) {
    return {code / W, code % W};
}

bool can_capture_a_white_group(const vector<string> &grid) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);

    const auto in_bounds = [&](const int ro, const int co) -> bool {
        return 0 <= ro && ro < H && 0 <= co && co < W;
    };

    atcoder::dsu g(H * W);
    unordered_set<int> leaders;
    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            if (grid[ro][co] != 'W') continue;

            for (const auto &[dr, dc] : Deltas) {
                const auto ro_ = ro + dr;
                const auto co_ = co + dc;
                if (!in_bounds(ro_, co_) || grid[ro_][co_] != 'W') continue;
                g.merge(ro * W + co, ro_ * W + co_);
            }
        }
    }

    for (const auto &codes : g.groups()) {
        {
            const auto [ro, co] = roco_of(W, codes[0]);
            if (grid[ro][co] != 'W') continue;
        }

        set<pii> empty_neighs;
        for (const auto c : codes) {
            const auto &[ro, co] = roco_of(W, c);
            for (const auto &[dr, dc] : Deltas) {
                const auto ro_ = ro + dr;
                const auto co_ = co + dc;
                if (!in_bounds(ro_, co_) || grid[ro_][co_] != '.') continue;
                empty_neighs.emplace(ro_, co_);
            }
        }
        if (sz(empty_neighs) == 1) return true;
    }

    return false;
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
        for (auto &row : grid) cin >> row;

        cout << "Case #" << i << ": "
             << (can_capture_a_white_group(grid) ? "YES" : "NO") << '\n';
    }

    return 0;
}
