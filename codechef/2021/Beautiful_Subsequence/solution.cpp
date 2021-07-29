#include <bits/stdc++.h>
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

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto xs : xss) os << xs << '\n';
    return os;
}

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int max_length_n2k(const int k, const vi &xs) {
    const auto n = sz(xs);
    vvi dp(k + 1, vi(n, 0));

    for (int j = 0; j <= k; ++j) {
        dp[j][0] = 1;
    }

    for (int i = 0; i < n; ++i) {
        dp[0][i] = 1;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= k; ++j) {
            for (int r = i + 1; r < n; ++r) {
                if (xs[i] == xs[r]) {
                    dp[j][r] = max(dp[j][r], dp[j][i] + 1);
                } else {
                    if (j < k) {
                        dp[j + 1][r] = max(dp[j + 1][r], dp[j][i] + 1);
                    }
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = max(ans, dp[k][i]);
    }
    return ans;
}

int max_length(const int k, const vi &xs) {
    const int n = sz(xs);

    vvi dp(k + 1, vi(n, 1));
    vector<map<int, int>> hi_idx_by_x(k + 1);

    for (int j = 0; j <= k; ++j) {
        hi_idx_by_x[j][xs[0]] = 0;
        dp[j][0] = 1;
    }

    vi hi_idx(k + 1, 0);

    for (int i = 1; i < n; ++i) {
        vector<pii> his;

        for (int j = 0; j <= k; ++j) {
            const auto p = hi_idx_by_x[j].find(xs[i]);
            bool new_hi = false;

            if (p != cend(hi_idx_by_x[j])) {
                dp[j][i] = dp[j][p->second] + 1;
                new_hi = true;
            }

            if (j > 0 && dp[j - 1][hi_idx[j - 1]] + 1 > dp[j][i]) {
                dp[j][i] = dp[j - 1][hi_idx[j - 1]] + 1;
                new_hi = true;
            }

            if (new_hi) {
                his.emplace_back(j, i);
            }
        }

        for (const auto [a, b] : his) {
            hi_idx_by_x[a][xs[b]] = b;
            hi_idx[a] = b;
        }
    }

    cerr << dp << endl;

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
        // assert(ans == max_length_n2k(k, xs));
        cout << ans << '\n';
    }

    return 0;
}
