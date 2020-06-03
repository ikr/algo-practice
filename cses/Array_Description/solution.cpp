#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
static const int M = 1e9 + 7;


template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto xs : xss) os << xs << '\n';
    return os;
}


int constrained_count(const int hi, const vi &counts_by_value, const int current_value) {
    int ans = counts_by_value[current_value];
    
    if (current_value > 0) {
        ans += counts_by_value[current_value - 1];
        ans %= M;
    }
    
    if (current_value < hi) {
        ans += counts_by_value[current_value + 1];
        ans %= M;
    }
    
    return ans;
}

int count_arrays(const int hi, const vi &xs) {
    const int sz = xs.size();
    
    // answer [up to index i] when [the i-th element is exactly j]
    vvi dp(sz, vi(hi + 1, 0));
    
    for (int i = 0; i != sz; ++i) {
        if (xs[i] != 0) {
            dp[i][xs[i]] = i == 0 ? 1 : constrained_count(hi, dp[i - 1], xs[i]);
        } else {
            for (int j = 1; j <= hi; ++j) {
                dp[i][j] = i == 0 ? 1 : constrained_count(hi, dp[i - 1], j);
            }
        }
    }
    
    // cout << dp << '\n';
    return *max_element(dp.back().cbegin(), dp.back().cend());
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int sz, hi;
    cin >> sz >> hi;

    vi xs(sz, 0);
    for (auto &x : xs) cin >> x;
    
    cout << count_arrays(hi, xs) << '\n';
    
    return 0;
}
