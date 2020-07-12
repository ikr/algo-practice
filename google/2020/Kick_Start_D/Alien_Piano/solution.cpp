#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;

vi gather_diffs(const vi &xs) {
    const int sz = xs.size();
    vi ans(sz, 0);
    for (int i = 1; i < sz; ++i) {
        if (xs[i] == xs[i - 1])
            ans[i] = 0;
        else
            ans[i] = xs[i] > xs[i - 1] ? 1 : -1;
    }
    return ans;
}

int solve(const vi &xs) {
    const int sz = xs.size();

    const auto diffs = gather_diffs(xs);
    vvi dp(sz, vi(4, 0));

    for (int i = 1; i < sz; ++i) {
        for (int j = 0; j <= 3; ++j) {
            if (diffs[i] == 0) {
                dp[i][j] = dp[i - 1][j];
            } else if (diffs[i] == 1) {
                if (j == 0) {
                    dp[i][j] =
                        1 + *min_element(dp[i - 1].cbegin(), dp[i - 1].cend());
                } else {
                    dp[i][j] = min(*min_element(dp[i - 1].cbegin(),
                                                dp[i - 1].cbegin() + j),
                                   1 + *min_element(dp[i - 1].cbegin() + j,
                                                    dp[i - 1].cend()));
                }
            } else if (diffs[i] == -1) {
                if (j == 3) {
                    dp[i][j] =
                        1 + *min_element(dp[i - 1].cbegin(), dp[i - 1].cend());
                } else {
                    dp[i][j] = min(*min_element(dp[i - 1].cbegin() + j + 1,
                                                dp[i - 1].cend()),
                                   1 + *min_element(dp[i - 1].cbegin(),
                                                    dp[i - 1].cbegin() + j));
                }
            }
        }
    }

    return *min_element(dp.back().cbegin(), dp.back().cend());
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int sz;
        cin >> sz;
        vi xs(sz, 0);
        for (auto &x : xs) cin >> x;
        cout << "Case #" << i << ": " << solve(xs) << '\n';
    }

    return 0;
}
