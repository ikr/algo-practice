#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
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
    assert(n <= 10);

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

int num_ways(const int n, const int m) {
    if (m == 1) return n % 2 ? 0 : 1;
    if (n == 1) return m % 2 ? 0 : 1;

    // dp[i][j] is number of ways at the row i, so that the i-th row's
    // horizontal occupancy bits are j
    vector<vector<mint>> dp(m, vector<mint>(1 << n, 0));

    for (int bits = 0; bits < (1 << n); ++bits) {
        if (is_possible_top_row(n, bits)) dp[0][bits] = 1;
    }

    for (int i = 1; i < m - 1; ++i) {
    }

    return accumulate(cbegin(dp.back()), cend(dp.back()), mint{0}).val();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    assert(is_possible_transition(10, 0, (1 << 10) - 1));
    assert(is_possible_transition(7, 0b1100110, 0b0011001));
    assert(!is_possible_transition(7, 0b1100110, 0b0010001));
    assert(is_possible_transition(7, 0b1100110, 0b0011111));
    assert(!is_possible_transition(7, 0b1100110, 0b1011001));
    assert(is_possible_transition(7, 0b1100110, 0b1111111));
    assert(is_possible_transition(8, (1 << 8) - 1, 0b01111110));
    assert(!is_possible_transition(8, (1 << 8) - 1, 0b01010101));

    int n, m;
    cin >> n >> m;
    cout << num_ways(n, m) << '\n';
    return 0;
}
