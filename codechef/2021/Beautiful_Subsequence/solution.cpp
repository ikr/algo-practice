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

map<int, vi> gather_indices(const vi &xs) {
    map<int, vi> ans;
    for (int i = 0; i < sz(xs); ++i) {
        ans[xs[i]].push_back(i);
    }
    return ans;
}

int max_length(const int k, const vi &xs) {
    const int n = sz(xs);
    const auto idx = gather_indices(xs);

    const auto prev_index = [&](const int x, const int i) -> int {
        assert(idx.count(x));
        const auto it = lower_bound(cbegin(idx.at(x)), cend(idx.at(x)), i);
        assert(it != cend(idx.at(x)));
        return it == cbegin(idx.at(x)) ? -1 : *prev(it);
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
        // assert(ans == max_length_n2k(k, xs));
        cout << ans << '\n';
    }

    return 0;
}
