#include <bits/stdc++.h>
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

vector<ll> max_score_by_moves(const vector<int> &ps, const vector<int> &xs) {
    const int n = xs.size();

    const auto rps = reverse_permutation(ps);

    // Score, when [standing at square i] after [exactly j moves used]
    vector<vector<ll>> dp(n, vector<ll>(n, 0));

    for (int j = 1; j < n; ++j) {
        for (int i = 0; i < n; ++i) {
            dp[i][j] = dp[rps[i]][j - 1] + xs[i];
        }
    }

    vector<ll> ans(n, LONG_LONG_MIN);
    ans[0] = 0;

    for (int j = 1; j < n; ++j) {
        for (int i = 0; i < n; ++i) {
            ans[j] = max(ans[j], dp[i][j]);
        }
    }

    return ans;
}

vector<vector<int>> gather_cycles(const vector<int> &ps) {
    const int n = ps.size();
    vector<vector<int>> ans;
    vector<bool> discovered(n, false);
    vector<int> curr;

    function<void(int)> dfs;
    dfs = [&dfs, &ans, &curr, &discovered, &ps](const int x) {
        discovered[x] = true;
        curr.push_back(x);
        const int y = ps[x];

        if (discovered[y]) {
            ans.push_back(curr);
            curr.clear();
        } else {
            dfs(y);
        }
    };

    for (const auto x : ps) {
        if (!discovered[x]) dfs(x);
    }

    return ans;
}

ll total_score(const vector<int> &xs, const vector<int> &indices) {
    ll ans = 0;
    for (const auto i : indices) ans += xs[i];
    return ans;
}

optional<pair<int, ll>> best_fitting_positive_cycle_length_and_score(
    const vector<int> &ps, const vector<int> &xs, const int k) {
    optional<pair<int, ll>> ans = nullopt;
    const auto cycles = gather_cycles(ps);

    for (const auto &ys : cycles) {
        const int sz = ys.size();
        if (k < sz) continue;

        const auto ys_score = total_score(xs, ys);
        if (ys_score <= 0) continue;

        if (!ans) {
            ans = {sz, ys_score};
            continue;
        }

        const ll champion = k / ans->first * ans->second;
        const ll candidate = k / sz * ys_score;

        if (candidate > champion) ans = {sz, ys_score};
    }

    return ans;
}

ll max_score(const vector<int> &ps, const vector<int> &xs, const int k) {
    const int n = xs.size();
    const auto sm = max_score_by_moves(ps, xs);

    const auto circuit =
        best_fitting_positive_cycle_length_and_score(ps, xs, k);

    if (!circuit) {
        return *max_element(sm.cbegin() + 1, sm.cbegin() + min(k + 1, n));
    } else {
        const auto [c_size, c_score] = *circuit;
        const int limitA = k % c_size + 1;
        const int limitB = min(k - (k / c_size - 1) * c_size + 1, n);

        return max(k / c_size * c_score +
                       *max_element(sm.cbegin() + 1, sm.cbegin() + limitA),
                   (k / c_size - 1) * c_score +
                       *max_element(sm.cbegin() + 1, sm.cbegin() + limitB));
    }
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
