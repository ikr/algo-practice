#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

static constexpr int INF = 1e9;

struct Move final {
    int damage;
    int loss;
};

int min_total_loss(const int S, const vector<Move> &mvs) {
    vector<vector<int>> dp(S + 1, vector<int>(sz(mvs), INF));
    for (int s = 0; s <= S; ++s) {
        dp[s][0] = div_ceil(s, mvs[0].damage) * mvs[0].loss;
    }

    for (int i = 0; i < sz(mvs); ++i) {
        dp[0][i] = 0;
    }

    for (int i = 1; i < sz(mvs); ++i) {
        for (int s = 1; s <= S; ++s) {
            const auto o1 = dp[s][i - 1];

            const auto o2 = [&]() -> int {
                const auto r = max(0, s - mvs[i].damage);
                return mvs[i].loss + dp[r][i];
            }();

            dp[s][i] = min(o1, o2);
        }
    }

    return dp.back().back();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int S, N;
    cin >> S >> N;

    vector<Move> mvs(N);
    for (auto &mv : mvs) {
        cin >> mv.damage >> mv.loss;
    }

    cout << min_total_loss(S, mvs) << '\n';
    return 0;
}
