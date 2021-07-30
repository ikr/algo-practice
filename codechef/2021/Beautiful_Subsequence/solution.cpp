#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

unordered_map<int, vi> gather_indices(const vi &xs) {
    unordered_map<int, vi> ans;
    for (int i = 0; i < sz(xs); ++i) {
        ans[xs[i]].push_back(i);
    }
    return ans;
}

int max_length(const int k, const vi &xs) {
    const int n = sz(xs);
    const auto idx = gather_indices(xs);

    const auto prev_index = [&idx](const int x, const int i) -> int {
        const auto &ii = idx.at(x);
        const auto it = lower_bound(cbegin(ii), cend(ii), i);
        return it == cbegin(ii) ? -1 : *prev(it);
    };

    vvi dp(k + 1, vi(n, 0));
    vvi hi(k + 1, vi(n, 1));

    for (int j = 0; j <= k; ++j) {
        dp[j][0] = 1;
    }

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= k; ++j) {
            if (j > 0) {
                dp[j][i] = hi[j - 1][i - 1] + 1;
            }

            const auto ii = prev_index(xs[i], i);
            if (ii >= 0) {
                dp[j][i] = max(dp[j][i], dp[j][ii] + 1);
            }

            if (j > 0) {
                hi[j][i] = max({hi[j - 1][i], hi[j][i - 1], dp[j][i]});
            } else {
                hi[j][i] = max({hi[j][i - 1], dp[j][i]});
            }
        }
    }

    return *max_element(cbegin(dp.back()), cend(dp.back()));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        vi xs(n);
        for (auto &x : xs) cin >> x;

        const auto ans = max_length(k, xs);
        cout << ans << '\n';
    }

    return 0;
}
