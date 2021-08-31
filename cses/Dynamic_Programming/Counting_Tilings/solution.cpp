#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using mint = atcoder::modint1000000007;

bool is_possible_upper_row(const int n, const int bits) {
    int span = (bits & 1) ? 1 : 0;
    for (int shift = 1; shift < n; ++shift) {
        if ((1 << shift) & bits) {
            ++span;
        } else {
            if (span % 2) return false;
            span = 0;
        }
    }

    return span % 2 == 0;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int num_ways(const int n, const int m) {
    if (m == 1) return n % 2 ? 0 : 1;
    if (n == 1) return m % 2 ? 0 : 1;

    // dp[i][j] is number of ways at the row i, so that the i-th row's
    // horizontal occupancy bits are j
    vector<vector<mint>> dp(m, vector<mint>(1 << n, 0));

    for (int bits = 0; bits < (1 << n); ++bits) {
        if (is_possible_upper_row(n, bits)) dp[0][bits] = 1;
    }

    for (int i = 1; i < m - 1; ++i) {

    }

    return accumulate(cbegin(dp.back()), cend(dp.back()), mint{0}).val();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;
    cout << num_ways(n, m) << '\n';
    return 0;
}
