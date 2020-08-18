#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto xs : xss) os << xs << '\n';
    return os;
}

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

ll max_score(const vector<int> &ps, const vector<int> &xs, const int k) {
    cout << gather_cycles(ps) << '\n';
    return 0;
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
