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

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int max_length(const int k, const vi &xs) {
    const auto n = sz(xs);
    vvi dp(k + 1, vi(n, 0));
    vi hi_idx(k + 1, 0);

    for (int j = 0; j <= k; ++j) {
        dp[j][0] = 1;
    }

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= k; ++j) {
            const auto hi0 = hi_idx[j];
            const auto hi1 = j > 0 ? hi_idx[j - 1] : hi0;

            const auto v = (hi0 == xs[i]) ? (dp[j][hi0] + 1)
                                          : (dp[max(0, j - 1)][hi1] + 1);

            dp[j][i] = v;

            if (v > dp[j][hi0]) {
                hi_idx[j] = j;
            }
        }
    }

    cerr << dp << endl;
    cerr << "hi_idx: " << hi_idx << endl;

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = max(ans, dp[k][i]);
    }
    return ans;
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

        cout << max_length(k, xs) << '\n';
    }

    return 0;
}
