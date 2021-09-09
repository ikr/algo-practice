#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using mint = atcoder::modint1000000007;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_possible_top_row(const int n, const int bits) {
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

bool is_possible_transition(const int n, const int bits_a, const int bits_b) {
    vi set_vars;
    for (int i = 0; i < n; ++i) {
        const int a = (1 << i) & bits_a;
        const int b = (1 << i) & bits_b;
        if (!a && !b) return false;
        if (a && b) set_vars.push_back(i);
    }

    if (sz(set_vars) % 2) return false;

    for (int i = 0; i < sz(set_vars); ++i) {
        if (i % 2 && set_vars[i] != set_vars[i - 1] + 1) return false;
    }

    return true;
}

vvi gather_successors(const int n) {
    vvi ans(1 << n);

    for (int bits_a = 0; bits_a < sz(ans); ++bits_a) {
        for (int bits_b = 0; bits_b < sz(ans); ++bits_b) {
            if (is_possible_transition(n, bits_a, bits_b)) {
                ans[bits_a].push_back(bits_b);
            }
        }
    }

    return ans;
}

int num_ways(const int n, const int m) {
    if (m == 1) return n % 2 ? 0 : 1;
    if (n == 1) return m % 2 ? 0 : 1;
    if ((n * m) % 2) return 0;

    const auto succ = gather_successors(n);

    // dp[i][j] is number of ways at the row i, so that the i-th row's
    // own occupancy bits are j
    vector<vector<mint>> dp(m, vector<mint>(1 << n, 0));

    for (int bits = 0; bits < (1 << n); ++bits) {
        if (is_possible_top_row(n, bits)) dp[0][bits] = 1;
    }

    for (int i = 0; i <= m - 3; ++i) {
        for (int bits_a = 0; bits_a < (1 << n); ++bits_a) {
            for (const auto bits_b : succ[bits_a]) {
                dp[i + 1][bits_b] += dp[i][bits_a];
            }
        }
    }

    for (int bits_a = 0; bits_a < (1 << n); ++bits_a) {
        if (is_possible_transition(n, bits_a, (1 << n) - 1)) {
            dp.back().back() += dp[m - 2][bits_a];
        }
    }

    return dp.back().back().val();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;
    cout << num_ways(n, m) << '\n';
    return 0;
}
