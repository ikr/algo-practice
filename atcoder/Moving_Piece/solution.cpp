#include <bits/stdc++.h>
#include <climits>
using namespace std;
using ll = long long;

vector<int> reverse_permutation(const vector<int> &ps) {
    const int n = ps.size();
    vector<int> ans(n, 0);

    for (int i = 0; i < n; ++i) {
        ans[ps[i]] = i;
    }

    return ans;
}

ll circuits_score(const vector<int> &xs, const ll k) {
    const ll n = xs.size();

    if (k / n) {
        const ll s = accumulate(xs.cbegin(), xs.cend(), 0LL, plus<ll>{});
        if (s > 0) return s * (k / n);
    }

    return 0;
}

ll max_score(const vector<int> &ps, const vector<int> &xs, const int k) {
    const int n = xs.size();

    const auto rps = reverse_permutation(ps);

    // Score, when [standing at square i] after [exactly j moves used]
    vector<vector<ll>> dp(n, vector<ll>(n, 0));

    for (int j = 1; j < n; ++j) {
        for (int i = 0; i < n; ++i) {
            dp[i][j] = dp[rps[i]][j - 1] + xs[i];
        }
    }

    ll a1 = LONG_LONG_MIN;
    ll a2 = LONG_LONG_MIN;
    for (const auto &row : dp) {
        for (int j = 1; j <= min(k, n - 1); ++j) {
            a1 = max(a1, row[j]);
        }

        for (int j = 1; j <= k % n; ++j) {
            a2 = max(a2, row[j]);
        }
    }

    cout << "cs:" << circuits_score(xs, k) << '\n';

    if (a1 != LONG_LONG_MIN && a2 != LONG_LONG_MIN) {
        return max(a1, a2 + circuits_score(xs, k));
    }

    return a1 != LONG_LONG_MIN ? a1 : a2;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    vector<int> ps(n, 0);
    for (auto &p : ps) {
        cin >> p;
        --p;
    }

    vector<int> xs(n, 0);
    for (auto &x : xs) cin >> x;

    cout << max_score(ps, xs, k) << '\n';

    return 0;
}
