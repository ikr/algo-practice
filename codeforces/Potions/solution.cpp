#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vll prefix_sums_with_zero(const vll &xs) {
    vll ans(sz(xs));
    partial_sum(cbegin(xs), cend(xs), begin(ans));
    ans.insert(cbegin(ans), 0LL);
    return ans;
}

int max_drinks(const vll &xs) {
    vector<map<ll, int>> dp(sz(xs));

    dp[0][xs[0]] = 1;

    for (int i = 1; i < sz(xs); ++i) {
        for (const auto [k, v] : dp[i - 1]) {
            dp[i][k] = max(dp[i][k], v);
            if (k  + xs[i] >= 0) {
                dp[i][k + xs[i]] = max(dp[i][k + xs[i]], v + 1);
            }
        }
    }

    int ans = 0;
    for (const auto [_, v] : dp.back()) {
        ans = max(ans, v);
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n;
    cin >> n;

    vll xs(n);
    for (auto &x : xs) cin >> x;

    cout << max_drinks(xs) << '\n';
    return 0;
}
