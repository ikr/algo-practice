#include <iostream>
#include <utility>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool can_reach_x(const int x, const vector<pair<int, int>> &ab) {
    const auto N = sz(ab);
    vector<vector<bool>> dp(N, vector(x + 1, false));
    if (ab[0].first <= x) dp[0][ab[0].first] = true;
    if (ab[0].second <= x) dp[0][ab[0].second] = true;

    for (int i = 1; i < sz(dp); ++i) {
        const auto [a, b] = ab[i];

        for (int k = 1; k + min(a, b) <= x; ++k) {
            if (dp[i - 1][k]) {
                if (k + a <= x) dp[i][k + a] = true;
                if (k + b <= x) dp[i][k + b] = true;
            }
        }
    }

    return dp.back()[x];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, X;
    cin >> N >> X;

    vector<pair<int, int>> ab(N);
    for (auto &[a, b] : ab) {
        cin >> a >> b;
    }

    cout << (can_reach_x(X, ab) ? "Yes" : "No") << '\n';
    return 0;
}
