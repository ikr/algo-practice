#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr ll INF = 1e18;

ll solve(const vector<vector<int>> &xss) {
    const auto N = sz(xss);
    assert(N <= 10);
    const auto P = sz(xss[0]);

    ll result = INF;
    vector<int> ord(N);
    iota(begin(ord), end(ord), 0);

    do {
        vector<vector<ll>> dp(N, vector<ll>(P, INF));

        for (int j = 0; j < P; ++j) {
            dp[0][j] = xss[ord[0]].back() + xss[ord[0]].back() - xss[ord[0]][j];
        }

        for (int i = 1; i < N; ++i) {
            for (int j = 0; j < P; ++j) {
                for (int k = 0; k < P; ++k) {
                    if (abs(xss[ord[i - 1]][k] - xss[ord[i]][0]) <=
                        abs(xss[ord[i - 1]][k] - xss[ord[i]].back())) {
                        dp[i][j] =
                            min(dp[i][j],
                                dp[i - 1][k] +
                                    abs(xss[ord[i - 1]][k] - xss[ord[i]][0]) +
                                    xss[ord[i]].back() - xss[ord[i]][0] +
                                    xss[ord[i]].back() - xss[ord[i]][j]);
                    } else {
                        dp[i][j] = min(
                            dp[i][j],
                            dp[i - 1][k] +
                                abs(xss[ord[i - 1]][k] - xss[ord[i]].back()) +
                                xss[ord[i]].back() - xss[ord[i]][0] +
                                xss[ord[i]][j] - xss[ord[i]][0]);
                    }
                }
            }
        }

        result = min(result, *min_element(cbegin(dp.back()), cend(dp.back())));
    } while (next_permutation(begin(ord), end(ord)));

    return result;
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
