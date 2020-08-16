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

ll max_score(const vector<int> &ps, const vector<int> &xs, const int k) {
    const int n = xs.size();
    const int r = k % n;
    const int q = k / n;

    ll ans = q ? q * accumulate(xs.cbegin(), xs.cend(), 0LL, plus<ll>{}) : 0LL;

    const auto rps = reverse_permutation(ps);
    vector<vector<pair<int, ll>>> dp(
        n, vector<pair<int, ll>>(r + 1, {0, LONG_LONG_MIN}));

    for (int i = 0; i < n; ++i) {
        dp[i][0] = {i, 0};
    }

    for (int j = 1; j <= r; ++j) {
        for (int i = 0; i < n; ++i) {
            const int idx = ps[dp[rps[i]][j - 1].first];
            const ll score = dp[rps[i]][j - 1].second + xs[ps[i]];
            dp[i][j] = {idx, score};
        }
    }

    ll addition = 0;
    for (const auto &row : dp) {
        for (const auto p : row) {
            addition = max(addition, p.second);
        }
    }

    return ans + addition;
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
