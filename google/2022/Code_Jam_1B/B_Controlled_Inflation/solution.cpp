#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
using namespace std;

using ll = long long;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr ll INF = 1e18;

ll coverage_cost(const ll src, const pair<ll, ll> ab, const ll dst) {
    const auto [a, b] = ab;
    assert(a <= b);
    return min(abs(src - a) + b - a + abs(b - dst),
               abs(src - b) + b - a + abs(dst - a));
}

ll solve(const vector<vector<int>> &xss) {
    const auto N = sz(xss);
    const auto P = sz(xss[0]);
    vector<vector<ll>> dp(N, vector<ll>(P, INF));

    for (int j = 0; j < P; ++j) {
        dp[0][j] = llof(xss[0].back()) + xss[0].back() - xss[0][j];
    }

    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < P; ++j) {
            for (int k = 0; k < P; ++k) {
                dp[i][j] =
                    min(dp[i][j],
                        dp[i - 1][k] + coverage_cost(xss[i - 1][k],
                                                     {xss[i][0], xss[i].back()},
                                                     xss[i][j]));
            }
        }
    }

    return *min_element(cbegin(dp.back()), cend(dp.back()));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N, P;
        cin >> N >> P;

        vector<vector<int>> xss(N, vector<int>(P, 0));
        for (auto &xs : xss) {
            for (auto &x : xs) cin >> x;
            sort(begin(xs), end(xs));
        }

        cout << "Case #" << i << ": " << solve(xss) << '\n';
    }

    return 0;
}
