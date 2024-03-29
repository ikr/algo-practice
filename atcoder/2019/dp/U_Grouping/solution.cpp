#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vll = vector<ll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll group_score(const vvi &compat, const int bits_group) {
    const int n = sz(compat);
    ll ans = 0;

    for (int i = 0; i < n - 1; ++i) {
        if ((1 << i) & bits_group) {
            for (int j = i + 1; j < n; ++j) {
                if ((1 << j) & bits_group) {
                    ans += compat[i][j];
                }
            }
        }
    }

    return ans;
}

vll group_scores(const vvi &compat) {
    const int n = sz(compat);
    vll ans(1 << n, 0);

    for (int bits = 1; bits < (1 << n); ++bits) {
        ans[bits] = group_score(compat, bits);
    }

    return ans;
}

constexpr int mlog2(const unsigned int x) {
    return inof(8U * sizeof(unsigned int) - __builtin_clz(x) - 1U);
}

vi popped_bits_indices(const int n) {
    const auto last = mlog2(n);
    vi ans;
    for (int i = 0; i <= last; ++i) {
        if (n & (1 << i)) ans.push_back(i);
    }
    return ans;
}

static constexpr ll INF = 1e18;

ll max_total_score(const vvi &compat) {
    const auto n = sz(compat);
    const auto score = group_scores(compat);

    // dp[i] is the max score over all the group assignments for a rabbits
    // bit-masked subset i
    vll dp(1 << n, -INF);
    dp[0] = 0;

    for (int bs = 1; bs < (1 << n); ++bs) {
        const auto idx = popped_bits_indices(bs);

        for (int i = 1; i < (1 << sz(idx)); ++i) {
            int sbs = 0;

            for (int j = 0; j < sz(idx); ++j) {
                if ((1 << j) & i) {
                    sbs |= (1 << idx[j]);
                }
            }

            dp[bs] = max(dp[bs], score[sbs] + dp[bs ^ sbs]);
        }
    }

    return dp.back();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vvi compat(n, vi(n, 0));
    for (auto &row : compat) {
        for (auto &x : row) {
            cin >> x;
        }
    }

    cout << max_total_score(compat) << '\n';
    return 0;
}
